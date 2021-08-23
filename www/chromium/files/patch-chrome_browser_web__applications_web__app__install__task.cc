--- chrome/browser/web_applications/web_app_install_task.cc.orig	2021-07-19 18:45:10 UTC
+++ chrome/browser/web_applications/web_app_install_task.cc
@@ -862,7 +862,7 @@ void WebAppInstallTask::OnInstallFinalizedCreateShortc
   options.os_hooks[OsHookType::kProtocolHandlers] = true;
   options.os_hooks[OsHookType::kUninstallationViaOsSettings] = true;
 #if defined(OS_WIN) || defined(OS_MAC) || \
-    (defined(OS_LINUX) && !BUILDFLAG(IS_CHROMEOS_LACROS))
+    (defined(OS_LINUX) && !BUILDFLAG(IS_CHROMEOS_LACROS)) || defined(OS_BSD)
   options.os_hooks[OsHookType::kUrlHandlers] = true;
 #else
   options.os_hooks[OsHookType::kUrlHandlers] = false;
