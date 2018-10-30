--- setup.py.orig	2018-10-29 20:57:30 UTC
+++ setup.py
@@ -166,7 +166,7 @@ setup(
         ]
     },
     scripts=['autokey-run', 'autokey-shell'],
-    install_requires=['dbus-python', 'pyinotify', 'python-xlib'],
+    install_requires=['pyinotify', 'python-xlib'],
     classifiers=[
         'Development Status :: 4 - Beta',
         'Intended Audience :: Developers',
