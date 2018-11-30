--- src/zm_signal.cpp.orig	2018-11-28 22:02:13 UTC
+++ src/zm_signal.cpp
@@ -63,17 +63,9 @@ RETSIGTYPE zm_die_handler(int signal)
 		ucontext_t *uc = (ucontext_t *) context;
 		cr2 = info->si_addr;
     #if defined(__x86_64__)
-	    #if defined(__FreeBSD_kernel__) || defined(__FreeBSD__) 
 		ip = (void *)(uc->uc_mcontext.mc_rip);
-	    #else
-		ip = (void *)(uc->uc_mcontext.gregs[REG_RIP]);
-	    #endif
     #else
-	    #if defined(__FreeBSD_kernel__) || defined(__FreeBSD__)
 		ip = (void *)(uc->uc_mcontext.mc_eip);
-	    #else
-		ip = (void *)(uc->uc_mcontext.gregs[REG_EIP]);
-	    #endif
     #endif				// defined(__x86_64__)
 
 		// Print the signal address and instruction pointer if available
