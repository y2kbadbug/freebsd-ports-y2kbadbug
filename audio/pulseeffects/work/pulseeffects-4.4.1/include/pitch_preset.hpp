#ifndef PITCH_PRESET_HPP
#define PITCH_PRESET_HPP

#include "plugin_preset_base.hpp"

class PitchPreset : public PluginPresetBase {
 public:
  PitchPreset();

  void write(boost::property_tree::ptree& root) override;
  void read(boost::property_tree::ptree& root) override;

 private:
  Glib::RefPtr<Gio::Settings> input_settings;

  void save(boost::property_tree::ptree& root,
            const std::string& section,
            const Glib::RefPtr<Gio::Settings>& settings) override;
  void load(boost::property_tree::ptree& root,
            const std::string& section,
            const Glib::RefPtr<Gio::Settings>& settings) override;
};

#endif
