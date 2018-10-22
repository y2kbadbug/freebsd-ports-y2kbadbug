--- guake/gsettings.py.orig	2018-10-09 03:47:12 UTC
+++ guake/gsettings.py
@@ -33,7 +33,7 @@ from gi.repository import Vte
 from guake.utils import RectCalculator
 
 from guake.common import pixmapfile
-from locale import gettext as _
+from gettext import gettext as _
 
 log = logging.getLogger(__name__)
 
