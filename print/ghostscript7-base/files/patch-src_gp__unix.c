--- src/gp_unix.c.orig	2003-01-17 09:49:02.000000000 +0900
+++ src/gp_unix.c	2015-08-22 02:44:59.415936000 +0900
@@ -41,11 +41,57 @@
 
 #endif
 
+#ifdef GS_DEVS_SHARED
+#ifndef GS_DEVS_SHARED_DIR
+#  define GS_DEVS_SHARED_DIR "/usr/lib/ghostscript/7.07"
+#endif
+
+/*
+ * use shared library for drivers, always load them when starting, this
+ * avoid too many modifications, and since it is supported only under linux
+ * and applied as a patch (preferable).
+ */
+#include <sys/types.h>
+#include <limits.h>
+#include <dirent.h>
+#include <dlfcn.h>
+#include <string.h>
+
+void
+gp_init(void)
+{
+  DIR*           dir = NULL;
+  struct dirent* dirent;
+  char           buff[PATH_MAX];
+  char*          pbuff;
+  void*          handle;
+  void           (*gs_shared_init)(void);
+
+  dir = opendir(GS_DEVS_SHARED_DIR);
+  if (dir == 0) return;
+
+  while ((dirent = readdir(dir)) != 0) {
+    snprintf(buff, sizeof(buff), "%s/%s", GS_DEVS_SHARED_DIR, dirent->d_name);
+    pbuff = buff + strlen(buff) - 3;
+    if (strcmp(pbuff, ".so") != 0)
+        continue;
+    handle = dlopen(buff, RTLD_NOW);
+    if (handle == NULL)
+        continue;
+    gs_shared_init = dlsym(handle, "gs_shared_init");
+    if (gs_shared_init != NULL)
+        (*gs_shared_init)();
+  }
+
+  closedir(dir);
+}
+#else
 /* Do platform-dependent initialization. */
 void
 gp_init(void)
 {
 }
+#endif
 
 /* Do platform-dependent cleanup. */
 void
@@ -57,6 +103,7 @@
 void
 gp_do_exit(int exit_status)
 {
+	exit(exit_status);
 }
 
 /* ------ Miscellaneous ------ */
@@ -67,7 +114,11 @@
 const char *
 gp_strerror(int errnum)
 {
+#ifdef HAVE_STRERROR
+    return strerror(errnum);
+#else
     return NULL;
+#endif
 }
 
 /* ------ Date and time ------ */
