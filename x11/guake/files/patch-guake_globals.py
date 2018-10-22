--- guake/globals.py.orig	2018-10-09 03:47:12 UTC
+++ guake/globals.py
@@ -50,7 +50,7 @@ def bindtextdomain(app_name, locale_dir=None):
     """
 
     import locale
-    from locale import gettext as _
+    from gettext import gettext as _
 
     log.info("Local binding for app '%s', local dir: %s", app_name, locale_dir)
 
