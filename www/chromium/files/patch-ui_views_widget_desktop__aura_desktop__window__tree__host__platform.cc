--- ui/views/widget/desktop_aura/desktop_window_tree_host_platform.cc.orig	2021-03-12 23:57:48 UTC
+++ ui/views/widget/desktop_aura/desktop_window_tree_host_platform.cc
@@ -818,7 +818,7 @@ void DesktopWindowTreeHostPlatform::AddAdditionalInitP
 // DesktopWindowTreeHost:
 
 // Linux subclasses this host and adds some Linux specific bits.
-#if !defined(OS_LINUX) && !defined(OS_CHROMEOS)
+#if !defined(OS_LINUX) && !defined(OS_CHROMEOS) && !defined(OS_BSD)
 // static
 DesktopWindowTreeHost* DesktopWindowTreeHost::Create(
     internal::NativeWidgetDelegate* native_widget_delegate,
