--- components/viz/service/frame_sinks/root_compositor_frame_sink_impl.h.orig	2021-03-12 23:57:23 UTC
+++ components/viz/service/frame_sinks/root_compositor_frame_sink_impl.h
@@ -165,7 +165,7 @@ class RootCompositorFrameSinkImpl : public mojom::Comp
 
 // TODO(crbug.com/1052397): Revisit the macro expression once build flag switch
 // of lacros-chrome is complete.
-#if defined(OS_LINUX) || BUILDFLAG(IS_CHROMEOS_LACROS)
+#if defined(OS_LINUX) || BUILDFLAG(IS_CHROMEOS_LACROS) || defined(OS_BSD)
   gfx::Size last_swap_pixel_size_;
 #endif
 
