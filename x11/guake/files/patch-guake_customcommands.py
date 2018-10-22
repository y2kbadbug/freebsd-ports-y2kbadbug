--- guake/customcommands.py.orig	2018-10-09 03:47:12 UTC
+++ guake/customcommands.py
@@ -4,7 +4,7 @@ import os
 import gi
 import logging
 
-from locale import gettext as _
+from gettext import gettext as _
 gi.require_version('Gtk', '3.0')
 from gi.repository import Gtk
 
