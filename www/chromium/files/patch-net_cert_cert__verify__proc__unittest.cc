--- net/cert/cert_verify_proc_unittest.cc.orig	2022-04-21 18:48:31 UTC
+++ net/cert/cert_verify_proc_unittest.cc
@@ -231,7 +231,7 @@ const std::vector<CertVerifyProcType> kAllCertVerifier
     CERT_VERIFY_PROC_MAC, CERT_VERIFY_PROC_BUILTIN
 #elif BUILDFLAG(IS_WIN)
     CERT_VERIFY_PROC_WIN, CERT_VERIFY_PROC_BUILTIN_CHROME_ROOTS
-#elif BUILDFLAG(IS_FUCHSIA) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
+#elif BUILDFLAG(IS_FUCHSIA) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_BSD)
     CERT_VERIFY_PROC_BUILTIN
 #else
 #error Unsupported platform
