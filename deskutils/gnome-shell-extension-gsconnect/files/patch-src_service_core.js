--- src/service/core.js.orig	2018-12-18 20:52:14 UTC
+++ src/service/core.js
@@ -113,8 +113,8 @@ var Channel = class Channel {
         if (connection instanceof Gio.TcpConnection) {
             connection.socket.set_keepalive(true);
             connection.socket.set_option(6, 4, 10); // TCP_KEEPIDLE
-            connection.socket.set_option(6, 5, 5);  // TCP_KEEPINTVL
-            connection.socket.set_option(6, 6, 3);  // TCP_KEEPCNT
+            // connection.socket.set_option(6, 5, 5);  // TCP_KEEPINTVL
+            // connection.socket.set_option(6, 6, 3);  // TCP_KEEPCNT
         }
 
         return connection;
