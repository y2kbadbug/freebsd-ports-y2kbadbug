--- chrome/browser/policy/configuration_policy_handler_list_factory.cc.orig	2022-06-17 14:20:10 UTC
+++ chrome/browser/policy/configuration_policy_handler_list_factory.cc
@@ -186,7 +186,7 @@
 #endif  // BUILDFLAG(ENABLE_SPELLCHECK)
 
 #if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
-    BUILDFLAG(IS_FUCHSIA)
+    BUILDFLAG(IS_FUCHSIA) || BUILDFLAG(IS_BSD)
 #include "chrome/browser/web_applications/policy/web_app_settings_policy_handler.h"
 #endif
 
@@ -1562,7 +1562,7 @@ const PolicyToPreferenceMapEntry kSimplePolicyMap[] = 
     base::Value::Type::BOOLEAN },
 #endif // !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_CHROMEOS)
 
-#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_CHROMEOS)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_BSD)
   { key::kAuthNegotiateDelegateByKdcPolicy,
     prefs::kAuthNegotiateDelegateByKdcPolicy,
     base::Value::Type::BOOLEAN },
@@ -1626,7 +1626,7 @@ const PolicyToPreferenceMapEntry kSimplePolicyMap[] = 
     base::Value::Type::BOOLEAN },
 #endif  // BUILDFLAG(IS_CHROMEOS_ASH)
 
-#if BUILDFLAG(ENABLE_EXTENSIONS) && (BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_FUCHSIA))
+#if BUILDFLAG(ENABLE_EXTENSIONS) && (BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_FUCHSIA) || BUILDFLAG(IS_BSD))
   { key::kChromeAppsEnabled,
     extensions::pref_names::kChromeAppsEnabled,
     base::Value::Type::BOOLEAN },
@@ -1945,7 +1945,7 @@ std::unique_ptr<ConfigurationPolicyHandlerList> BuildH
       key::kBrowsingDataLifetime, browsing_data::prefs::kBrowsingDataLifetime,
       chrome_schema));
 
-#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN) || BUILDFLAG(IS_BSD)
   handlers->AddHandler(std::make_unique<LocalSyncPolicyHandler>());
   handlers->AddHandler(std::make_unique<ThemeColorPolicyHandler>());
 #endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN)
@@ -2299,7 +2299,7 @@ std::unique_ptr<ConfigurationPolicyHandlerList> BuildH
       static_cast<int>(variations::RestrictionPolicy::ALL), false));
 
 #if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
-    BUILDFLAG(IS_FUCHSIA)
+    BUILDFLAG(IS_FUCHSIA) || BUILDFLAG(IS_BSD)
   handlers->AddHandler(
       std::make_unique<web_app::WebAppSettingsPolicyHandler>(chrome_schema));
 #endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) ||
@@ -2318,7 +2318,7 @@ std::unique_ptr<ConfigurationPolicyHandlerList> BuildH
           policy::key::kSpellcheckLanguageBlocklist));
 #endif  // BUILDFLAG(ENABLE_SPELLCHECK)
 
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   handlers->AddHandler(std::make_unique<SimplePolicyHandler>(
       key::kAllowSystemNotifications, prefs::kAllowSystemNotifications,
       base::Value::Type::BOOLEAN));
