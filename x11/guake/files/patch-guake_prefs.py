--- guake/prefs.py.orig	2018-10-09 03:47:12 UTC
+++ guake/prefs.py
@@ -59,7 +59,7 @@ from guake.simplegladeapp import SimpleGladeApp
 from guake.terminal import GuakeTerminal
 from guake.theme import list_all_themes
 from guake.theme import select_gtk_theme
-from locale import gettext as _
+from gettext import gettext as _
 
 # pylint: disable=unsubscriptable-object
 
