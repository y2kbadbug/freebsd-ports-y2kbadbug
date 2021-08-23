--- headless/lib/browser/headless_content_browser_client.cc.orig	2021-07-19 18:45:17 UTC
+++ headless/lib/browser/headless_content_browser_client.cc
@@ -288,7 +288,7 @@ void HeadlessContentBrowserClient::AppendExtraCommandL
                                             process_type, child_process_id);
   }
 
-#if defined(OS_LINUX) || defined(OS_CHROMEOS)
+#if defined(OS_LINUX) || defined(OS_CHROMEOS) || defined(OS_BSD)
   // Processes may only query perf_event_open with the BPF sandbox disabled.
   if (old_command_line.HasSwitch(::switches::kEnableThreadInstructionCount) &&
       old_command_line.HasSwitch(sandbox::policy::switches::kNoSandbox)) {
