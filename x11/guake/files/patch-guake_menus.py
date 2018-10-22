--- guake/menus.py.orig	2018-10-09 03:47:12 UTC
+++ guake/menus.py
@@ -1,7 +1,7 @@
 import gi
 gi.require_version('Gtk', '3.0')
 from gi.repository import Gtk
-from locale import gettext as _
+from gettext import gettext as _
 gi.require_version('Vte', '2.91')  # vte-0.42
 from gi.repository import Vte
 from guake.customcommands import CustomCommands
