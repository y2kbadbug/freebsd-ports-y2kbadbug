--- components/viz/service/frame_sinks/root_compositor_frame_sink_impl.cc.orig	2021-05-12 22:05:52 UTC
+++ components/viz/service/frame_sinks/root_compositor_frame_sink_impl.cc
@@ -60,7 +60,7 @@ RootCompositorFrameSinkImpl::Create(
 
 // TODO(crbug.com/1052397): Revisit the macro expression once build flag switch
 // of lacros-chrome is complete.
-#if defined(OS_LINUX) || BUILDFLAG(IS_CHROMEOS_LACROS)
+#if defined(OS_LINUX) || BUILDFLAG(IS_CHROMEOS_LACROS) || defined(OS_BSD)
   // For X11, we need notify client about swap completion after resizing, so the
   // client can use it for synchronize with X11 WM.
   output_surface->SetNeedsSwapSizeNotifications(true);
@@ -479,7 +479,7 @@ void RootCompositorFrameSinkImpl::DisplayDidCompleteSw
     display_client_->DidCompleteSwapWithSize(pixel_size);
 // TODO(crbug.com/1052397): Revisit the macro expression once build flag switch
 // of lacros-chrome is complete.
-#elif defined(OS_LINUX) || BUILDFLAG(IS_CHROMEOS_LACROS)
+#elif defined(OS_LINUX) || BUILDFLAG(IS_CHROMEOS_LACROS) || defined(OS_BSD)
   if (display_client_ && pixel_size != last_swap_pixel_size_) {
     last_swap_pixel_size_ = pixel_size;
     display_client_->DidCompleteSwapWithNewSize(last_swap_pixel_size_);
