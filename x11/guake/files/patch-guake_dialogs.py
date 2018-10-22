--- guake/dialogs.py.orig	2018-10-09 03:47:12 UTC
+++ guake/dialogs.py
@@ -1,7 +1,7 @@
 import gi
 gi.require_version('Gtk', '3.0')
 from gi.repository import Gtk
-from locale import gettext as _
+from gettext import gettext as _
 
 
 class RenameDialog(Gtk.Dialog):
