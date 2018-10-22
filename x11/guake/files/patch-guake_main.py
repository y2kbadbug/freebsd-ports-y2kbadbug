--- guake/main.py.orig	2018-10-09 03:47:12 UTC
+++ guake/main.py
@@ -31,7 +31,7 @@ import subprocess
 import sys
 import uuid
 
-from locale import gettext as _
+from gettext import gettext as _
 from optparse import OptionParser
 
 log = logging.getLogger(__name__)
