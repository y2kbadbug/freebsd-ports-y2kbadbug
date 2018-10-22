--- guake/keybindings.py.orig	2018-10-09 03:47:12 UTC
+++ guake/keybindings.py
@@ -27,7 +27,7 @@ from guake import notifier
 from guake.common import pixmapfile
 from guake.split_utils import FocusMover
 from guake.split_utils import SplitMover
-from locale import gettext as _
+from gettext import gettext as _
 
 log = logging.getLogger(__name__)
 
