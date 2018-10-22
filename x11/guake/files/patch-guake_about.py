--- guake/about.py.orig	2018-10-09 03:47:12 UTC
+++ guake/about.py
@@ -28,7 +28,7 @@ from guake import guake_version
 from guake.common import gladefile
 from guake.common import pixmapfile
 from guake.simplegladeapp import SimpleGladeApp
-from locale import gettext as _
+from gettext import gettext as _
 
 
 class AboutDialog(SimpleGladeApp):
