--- guake/notebook.py.orig	2018-10-09 03:47:12 UTC
+++ guake/notebook.py
@@ -32,7 +32,7 @@ from gi.repository import GObject
 from gi.repository import Gdk
 from gi.repository import Gtk
 from guake.terminal import GuakeTerminal
-from locale import gettext as _
+from gettext import gettext as _
 
 import logging
 import posix
