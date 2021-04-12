--- net/url_request/url_request_context.cc.orig	2021-03-12 23:57:27 UTC
+++ net/url_request/url_request_context.cc
@@ -93,7 +93,7 @@ const HttpNetworkSession::Context* URLRequestContext::
 
 // TODO(crbug.com/1052397): Revisit once build flag switch of lacros-chrome is
 // complete.
-#if !defined(OS_WIN) && !(defined(OS_LINUX) || BUILDFLAG(IS_CHROMEOS_LACROS))
+#if !defined(OS_WIN) && !(defined(OS_LINUX) || BUILDFLAG(IS_CHROMEOS_LACROS) || defined(OS_BSD))
 std::unique_ptr<URLRequest> URLRequestContext::CreateRequest(
     const GURL& url,
     RequestPriority priority,
