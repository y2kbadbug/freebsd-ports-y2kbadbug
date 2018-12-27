#include "pipeline_base.hpp"
#include <glib-object.h>
#include <gobject/gvaluecollector.h>
#include <algorithm>
#include <boost/math/interpolators/cubic_b_spline.hpp>
#include <cmath>
#include <mutex>
#include "config.h"
#include "util.hpp"

namespace {

void on_message_error(const GstBus* gst_bus,
                      GstMessage* message,
                      PipelineBase* pb) {
  GError* err;
  gchar* debug;

  gst_message_parse_error(message, &err, &debug);

  util::critical(pb->log_tag + err->message);
  util::debug(pb->log_tag + debug);

  pb->set_null_pipeline();

  g_error_free(err);
  g_free(debug);
}

void on_message_state_changed(const GstBus* gst_bus,
                              GstMessage* message,
                              PipelineBase* pb) {
  if (GST_OBJECT_NAME(message->src) == std::string("pipeline")) {
    GstState old_state, new_state, pending;

    gst_message_parse_state_changed(message, &old_state, &new_state, &pending);

    util::debug(pb->log_tag + gst_element_state_get_name(old_state) + " -> " +
                gst_element_state_get_name(new_state) + " -> " +
                gst_element_state_get_name(pending));

    if (new_state == GST_STATE_PLAYING) {
      pb->playing = true;
      pb->get_latency();
    } else {
      pb->playing = false;
    }
  }
}

void on_message_latency(const GstBus* gst_bus,
                        GstMessage* message,
                        PipelineBase* pb) {
  if (GST_OBJECT_NAME(message->src) == std::string("source")) {
    int latency, buffer;

    g_object_get(pb->source, "latency-time", &latency, nullptr);
    g_object_get(pb->source, "buffer-time", &buffer, nullptr);

    util::debug(pb->log_tag +
                "pulsesrc latency [us]: " + std::to_string(latency));
    util::debug(pb->log_tag +
                "pulsesrc buffer [us]: " + std::to_string(buffer));
  } else if (GST_OBJECT_NAME(message->src) == std::string("sink")) {
    int latency, buffer;

    g_object_get(pb->sink, "latency-time", &latency, nullptr);
    g_object_get(pb->sink, "buffer-time", &buffer, nullptr);

    util::debug(pb->log_tag +
                "pulsesink latency [us]: " + std::to_string(latency));
    util::debug(pb->log_tag +
                "pulsesink buffer [us]: " + std::to_string(buffer));
  }
}

void on_message_element(const GstBus* gst_bus,
                        GstMessage* message,
                        PipelineBase* pb) {
  if (GST_OBJECT_NAME(message->src) == std::string("spectrum") &&
      !pb->resizing_spectrum) {
    const GstStructure* s = gst_message_get_structure(message);

    const GValue* magnitudes;

    magnitudes = gst_structure_get_value(s, "magnitude");

    for (uint n = 0; n < pb->spectrum_freqs.size(); n++) {
      pb->spectrum_mag_tmp[n] =
          g_value_get_float(gst_value_list_get_value(magnitudes, n));
    }

    try {
      boost::math::cubic_b_spline<float> spline(pb->spectrum_mag_tmp.begin(),
                                                pb->spectrum_mag_tmp.end(),
                                                pb->spline_f0, pb->spline_df);

      for (uint n = 0; n < pb->spectrum_mag.size(); n++) {
        pb->spectrum_mag[n] = spline(pb->spectrum_x_axis[n]);
      }
    } catch (const std::exception& e) {
      util::debug(std::string("Message from thrown exception was: ") +
                  e.what());
    }

    auto min_mag = pb->spectrum_threshold;
    auto max_mag =
        *std::max_element(pb->spectrum_mag.begin(), pb->spectrum_mag.end());

    if (max_mag > min_mag) {
      for (uint n = 0; n < pb->spectrum_mag.size(); n++) {
        pb->spectrum_mag[n] = (min_mag - pb->spectrum_mag[n]) / min_mag;
      }

      Glib::signal_idle().connect_once(
          [=] { pb->new_spectrum.emit(pb->spectrum_mag); });
    }
  }
}

void on_spectrum_n_points_changed(GSettings* settings,
                                  gchar* key,
                                  PipelineBase* pb) {
  long unsigned int npoints = g_settings_get_int(settings, "spectrum-n-points");

  if (npoints != pb->spectrum_mag.size()) {
    pb->resizing_spectrum = true;

    pb->spectrum_mag.resize(npoints);

    pb->spectrum_x_axis = util::logspace(log10(pb->min_spectrum_freq),
                                         log10(pb->max_spectrum_freq), npoints);

    pb->resizing_spectrum = false;
  }
}

void on_src_type_changed(GstElement* typefind,
                         guint probability,
                         GstCaps* caps,
                         PipelineBase* pb) {
  GstStructure* structure = gst_caps_get_structure(caps, 0);

  int rate;

  gst_structure_get_int(structure, "rate", &rate);

  pb->init_spectrum(rate);

  util::debug(pb->log_tag + "sampling rate: " + std::to_string(rate) + " Hz");
}

void on_buffer_changed(GObject* gobject, GParamSpec* pspec, PipelineBase* pb) {
  GstState state, pending;

  gst_element_get_state(pb->pipeline, &state, &pending,
                        pb->state_check_timeout);

  if (state == GST_STATE_PLAYING || state == GST_STATE_PAUSED) {
    /*when we are playing it is necessary to reset the pipeline for the new
     * value to take effect
     */

    gst_element_set_state(pb->pipeline, GST_STATE_READY);

    pb->update_pipeline_state();
  }
}

void on_latency_changed(GObject* gobject, GParamSpec* pspec, PipelineBase* pb) {
  GstState state, pending;

  gst_element_get_state(pb->pipeline, &state, &pending,
                        pb->state_check_timeout);

  if (state == GST_STATE_PLAYING || state == GST_STATE_PAUSED) {
    /*when we are playing it is necessary to reset the pipeline for the new
     * value to take effect
     */

    gst_element_set_state(pb->pipeline, GST_STATE_READY);

    pb->update_pipeline_state();
  }
}

}  // namespace

PipelineBase::PipelineBase(const std::string& tag, const uint& sampling_rate)
    : log_tag(tag), settings(g_settings_new("com.github.wwmm.pulseeffects")) {
  gst_init(nullptr, nullptr);

  pipeline = gst_pipeline_new("pipeline");

  bus = gst_element_get_bus(pipeline);

  gst_bus_add_signal_watch(bus);

  // bus callbacks

  g_signal_connect(bus, "message::error", G_CALLBACK(on_message_error), this);
  g_signal_connect(bus, "message::state-changed",
                   G_CALLBACK(on_message_state_changed), this);
  g_signal_connect(bus, "message::latency", G_CALLBACK(on_message_latency),
                   this);
  g_signal_connect(bus, "message::element", G_CALLBACK(on_message_element),
                   this);

  // creating elements common to all pipelines

  gst_registry_scan_path(gst_registry_get(), PLUGINS_INSTALL_DIR);

  source = get_required_plugin("pulsesrc", "source");
  capsfilter = get_required_plugin("capsfilter", nullptr);
  adapter = get_required_plugin("peadapter", nullptr);
  sink = get_required_plugin("pulsesink", "sink");
  spectrum = get_required_plugin("spectrum", "spectrum");

  auto queue_src = get_required_plugin("queue", nullptr);
  auto src_type = get_required_plugin("typefind", nullptr);
  auto audioconvert_in = get_required_plugin("audioconvert", nullptr);
  auto audioconvert_out = get_required_plugin("audioconvert", nullptr);

  init_spectrum_bin();
  init_effects_bin();

  // building the pipeline

  gst_bin_add_many(GST_BIN(pipeline), source, queue_src, capsfilter, src_type,
                   audioconvert_in, adapter, audioconvert_out, effects_bin,
                   spectrum_bin, sink, nullptr);

  gst_element_link_many(source, queue_src, capsfilter, src_type,
                        audioconvert_in, adapter, audioconvert_out, effects_bin,
                        spectrum_bin, sink, nullptr);

  // initializing properties

  g_object_set(source, "volume", 1.0, nullptr);
  g_object_set(source, "mute", false, nullptr);
  g_object_set(source, "provide-clock", false, nullptr);
  g_object_set(source, "slave-method", 1, nullptr);  // re-timestamp
  g_object_set(source, "do-timestamp", true, nullptr);

  g_object_set(sink, "volume", 1.0, nullptr);
  g_object_set(sink, "mute", false, nullptr);
  g_object_set(sink, "provide-clock", true, nullptr);

  g_object_set(queue_src, "silent", true, nullptr);
  g_object_set(queue_src, "max-size-buffers", 0, nullptr);
  g_object_set(queue_src, "max-size-bytes", 0, nullptr);
  g_object_set(queue_src, "max-size-time", 0, nullptr);

  g_object_set(spectrum, "bands", spectrum_nbands, nullptr);
  g_object_set(spectrum, "threshold", spectrum_threshold, nullptr);

  set_caps(sampling_rate);

  g_signal_connect(src_type, "have-type", G_CALLBACK(on_src_type_changed),
                   this);
  g_signal_connect(source, "notify::buffer-time", G_CALLBACK(on_buffer_changed),
                   this);
  g_signal_connect(source, "notify::latency-time",
                   G_CALLBACK(on_latency_changed), this);
}

PipelineBase::~PipelineBase() {
  set_null_pipeline();

  // avoinding memory leak. If the spectrum is not in a bin we have to unref
  // it

  auto s = gst_bin_get_by_name(GST_BIN(spectrum_bin), "spectrum");

  if (!s) {
    gst_object_unref(spectrum);
  }

  gst_object_unref(bus);
  gst_object_unref(pipeline);
  g_object_unref(settings);
}

void PipelineBase::set_caps(const uint& sampling_rate) {
  auto caps_str = "audio/x-raw,format=F32LE,channels=2,rate=" +
                  std::to_string(sampling_rate);

  auto caps = gst_caps_from_string(caps_str.c_str());

  g_object_set(capsfilter, "caps", caps, nullptr);

  gst_caps_unref(caps);
}

void PipelineBase::init_spectrum_bin() {
  spectrum_bin = gst_bin_new("spectrum_bin");
  spectrum_identity_in = gst_element_factory_make("identity", nullptr);
  spectrum_identity_out = gst_element_factory_make("identity", nullptr);

  gst_bin_add_many(GST_BIN(spectrum_bin), spectrum_identity_in,
                   spectrum_identity_out, nullptr);

  gst_element_link(spectrum_identity_in, spectrum_identity_out);

  auto sinkpad = gst_element_get_static_pad(spectrum_identity_in, "sink");
  auto srcpad = gst_element_get_static_pad(spectrum_identity_out, "src");

  gst_element_add_pad(spectrum_bin, gst_ghost_pad_new("sink", sinkpad));
  gst_element_add_pad(spectrum_bin, gst_ghost_pad_new("src", srcpad));

  g_object_unref(sinkpad);
  g_object_unref(srcpad);
}

void PipelineBase::init_effects_bin() {
  effects_bin = gst_bin_new("effects_bin");

  identity_in = gst_element_factory_make("identity", nullptr);
  identity_out = gst_element_factory_make("identity", nullptr);

  gst_bin_add_many(GST_BIN(effects_bin), identity_in, identity_out, nullptr);

  gst_element_link(identity_in, identity_out);

  auto sinkpad = gst_element_get_static_pad(identity_in, "sink");
  auto srcpad = gst_element_get_static_pad(identity_out, "src");

  gst_element_add_pad(effects_bin, gst_ghost_pad_new("sink", sinkpad));
  gst_element_add_pad(effects_bin, gst_ghost_pad_new("src", srcpad));

  g_object_unref(sinkpad);
  g_object_unref(srcpad);
}

void PipelineBase::set_source_monitor_name(std::string name) {
  gchar* current_device;

  g_object_get(source, "current-device", &current_device, nullptr);

  if (name != current_device) {
    if (playing) {
      set_null_pipeline();

      g_object_set(source, "device", name.c_str(), nullptr);

      gst_element_set_state(pipeline, GST_STATE_PLAYING);
    } else {
      g_object_set(source, "device", name.c_str(), nullptr);
    }

    util::debug(log_tag + "using input device: " + name);
  }

  g_free(current_device);
}

void PipelineBase::set_output_sink_name(std::string name) {
  g_object_set(sink, "device", name.c_str(), nullptr);

  util::debug(log_tag + "using output device: " + name);
}

void PipelineBase::set_pulseaudio_props(std::string props) {
  auto str = "props," + props;

  auto s = gst_structure_from_string(str.c_str(), nullptr);

  g_object_set(source, "stream-properties", s, nullptr);
  g_object_set(sink, "stream-properties", s, nullptr);

  gst_structure_free(s);
}

void PipelineBase::set_null_pipeline() {
  gst_element_set_state(pipeline, GST_STATE_NULL);

  GstState state, pending;

  gst_element_get_state(pipeline, &state, &pending, state_check_timeout);

  /*on_message_state is not called when going to null. I don't know why.
   * so we have to update the variable manually after setting to null.
   */

  if (state == GST_STATE_NULL) {
    playing = false;
  }

  util::debug(log_tag + gst_element_state_get_name(state) + " -> " +
              gst_element_state_get_name(pending));
}

void PipelineBase::update_pipeline_state() {
  bool wants_to_play = false;

  for (auto& a : apps_list) {
    if (a->wants_to_play) {
      wants_to_play = true;

      break;
    }
  }

  GstState state, pending;

  gst_element_get_state(pipeline, &state, &pending, state_check_timeout);

  if (state != GST_STATE_PLAYING && wants_to_play) {
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
  } else if (state == GST_STATE_PLAYING && !wants_to_play) {
    gst_element_set_state(pipeline, GST_STATE_READY);
  }
}

void PipelineBase::get_latency() {
  GstQuery* q = gst_query_new_latency();

  if (gst_element_query(pipeline, q)) {
    gboolean live;
    GstClockTime min, max;

    gst_query_parse_latency(q, &live, &min, &max);

    int latency = GST_TIME_AS_MSECONDS(min);

    util::debug(log_tag + "total latency: " + std::to_string(latency) + " ms");

    Glib::signal_idle().connect_once([=] { new_latency.emit(latency); });
  }

  gst_query_unref(q);
}

void PipelineBase::on_app_added(const std::shared_ptr<AppInfo>& app_info) {
  for (auto a : apps_list) {
    if (a->index == app_info->index) {
      // do not add the same app two times in the interface
      return;
    }
  }

  apps_list.push_back(move(app_info));

  update_pipeline_state();
}

void PipelineBase::on_app_changed(const std::shared_ptr<AppInfo>& app_info) {
  std::replace_copy_if(apps_list.begin(), apps_list.end(), apps_list.begin(),
                       [=](auto& a) { return a->index == app_info->index; },
                       move(app_info));

  update_pipeline_state();
}

void PipelineBase::on_app_removed(uint idx) {
  apps_list.erase(std::remove_if(apps_list.begin(), apps_list.end(),
                                 [=](auto& a) { return a->index == idx; }),
                  apps_list.end());

  update_pipeline_state();
}

void PipelineBase::init_spectrum(const uint& sampling_rate) {
  g_signal_connect(settings, "changed::spectrum-n-points",
                   G_CALLBACK(on_spectrum_n_points_changed), this);

  spectrum_freqs.clear();

  for (uint n = 0; n < spectrum_nbands; n++) {
    auto f = sampling_rate * (0.5 * n + 0.25) / spectrum_nbands;

    if (f > max_spectrum_freq) {
      break;
    }

    if (f > min_spectrum_freq) {
      spectrum_freqs.push_back(f);
    }
  }

  spectrum_mag_tmp.resize(spectrum_freqs.size());

  auto npoints = g_settings_get_int(settings, "spectrum-n-points");

  spectrum_x_axis = util::logspace(log10(min_spectrum_freq),
                                   log10(max_spectrum_freq), npoints);

  spectrum_mag.resize(npoints);

  spline_f0 = spectrum_freqs[0];
  spline_df = spectrum_freqs[1] - spectrum_freqs[0];
}

void PipelineBase::enable_spectrum() {
  auto srcpad = gst_element_get_static_pad(spectrum_identity_in, "src");

  auto id = gst_pad_add_probe(
      srcpad, GST_PAD_PROBE_TYPE_IDLE,
      [](auto pad, auto info, auto d) {
        auto l = static_cast<PipelineBase*>(d);

        std::lock_guard<std::mutex> lock(l->pipeline_mutex);

        auto plugin = gst_bin_get_by_name(GST_BIN(l->spectrum_bin), "spectrum");

        if (!plugin) {
          gst_element_unlink(l->spectrum_identity_in, l->spectrum_identity_out);

          gst_bin_add(GST_BIN(l->spectrum_bin), l->spectrum);

          gst_element_link_many(l->spectrum_identity_in, l->spectrum,
                                l->spectrum_identity_out, nullptr);

          gst_element_sync_state_with_parent(l->spectrum);

          util::debug(l->log_tag + "spectrum enabled");
        } else {
          util::debug(l->log_tag + "spectrum is already enabled");
        }

        return GST_PAD_PROBE_REMOVE;
      },
      this, nullptr);

  if (id != 0) {
    util::debug(log_tag + " spectrum will be enabled in another thread");
  }

  g_object_unref(srcpad);
}

void PipelineBase::disable_spectrum() {
  auto srcpad = gst_element_get_static_pad(spectrum_identity_in, "src");

  auto id = gst_pad_add_probe(
      srcpad, GST_PAD_PROBE_TYPE_IDLE,
      [](auto pad, auto info, auto d) {
        auto l = static_cast<PipelineBase*>(d);

        std::lock_guard<std::mutex> lock(l->pipeline_mutex);

        auto plugin = gst_bin_get_by_name(GST_BIN(l->spectrum_bin), "spectrum");

        if (plugin) {
          gst_element_set_state(l->spectrum, GST_STATE_NULL);

          gst_element_unlink_many(l->spectrum_identity_in, l->spectrum,
                                  l->spectrum_identity_out, nullptr);

          gst_bin_remove(GST_BIN(l->spectrum_bin), l->spectrum);

          gst_element_link(l->spectrum_identity_in, l->spectrum_identity_out);

          util::debug(l->log_tag + "spectrum disabled");
        } else {
          util::debug(l->log_tag + "spectrum is already disabled");
        }

        return GST_PAD_PROBE_REMOVE;
      },
      this, nullptr);

  if (id != 0) {
    util::debug(log_tag + " spectrum will be disabled in another thread");
  }

  g_object_unref(srcpad);
}

std::array<double, 2> PipelineBase::get_peak(GstMessage* message) {
  std::array<double, 2> peak;

  const GstStructure* s = gst_message_get_structure(message);

  auto gpeak =
      (GValueArray*)g_value_get_boxed(gst_structure_get_value(s, "peak"));

  if (gpeak != nullptr) {
    if (gpeak->n_values == 2) {
      if (gpeak->values != nullptr) {
        peak[0] = g_value_get_double(gpeak->values);      // left
        peak[1] = g_value_get_double(gpeak->values + 1);  // right
      }
    }
  }

  return peak;
}

GstElement* PipelineBase::get_required_plugin(const gchar* factoryname,
                                              const gchar* name) {
  GstElement* plugin = gst_element_factory_make(factoryname, name);

  if (!plugin)
    throw std::runtime_error(
        log_tag + std::string("Failed to get required plugin: ") + factoryname);

  return plugin;
}
