--- guake/boxes.py.orig	2018-10-09 03:47:12 UTC
+++ guake/boxes.py
@@ -1,6 +1,6 @@
 import logging
 
-from locale import gettext as _
+from gettext import gettext as _
 
 import gi
 gi.require_version('Vte', '2.91')  # vte-0.42
