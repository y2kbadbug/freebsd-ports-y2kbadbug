--- guake/guake_app.py.orig	2018-10-09 03:47:12 UTC
+++ guake/guake_app.py
@@ -82,7 +82,7 @@ from guake.utils import RectCalculator
 from guake.utils import TabNameUtils
 from guake.utils import get_server_time
 
-from locale import gettext as _
+from gettext import gettext as _
 
 log = logging.getLogger(__name__)
 
