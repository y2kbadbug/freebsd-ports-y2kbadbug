--- chrome/common/url_constants.cc.orig	2022-04-21 18:48:31 UTC
+++ chrome/common/url_constants.cc
@@ -489,7 +489,7 @@ const char kPhoneHubPermissionLearnMoreURL[] =
     "https://support.google.com/chromebook/?p=multidevice";
 
 #if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
-    BUILDFLAG(IS_FUCHSIA)
+    BUILDFLAG(IS_FUCHSIA) || BUILDFLAG(IS_BSD)
 const char kChromeAppsDeprecationLearnMoreURL[] =
     "https://support.google.com/chrome/?p=chrome_app_deprecation";
 #endif
