To develop a barrier synchronization mechanism in Linux kernel that can be invoked by user processes via system call interface.

This folder contains
1. Patch file that consists of changes to the original kernel source code - syscalls_32_tbl.patch, sys.patch, syscalls_h.patch
2. User program - user.c
3. Makefile (to make the user program),
4. README file
5. console output
6. dmesg output

Steps to follow:
1. Patch the diff to the kernel module using the below commands from linux directory and compile the new kernel:
	"patch arch/x86/syscalls/syscall_32.tbl < syscalls_32_tbl.patch"  [for syscall_32.tbl]
	"patch kernel/sys.c < sys.patch"   [syscall.c ]
	"patch include/linux/syscalls.h < syscalls_h.patch" [syscalls.h]
 
2. Use Makefile to compile the user program --> #make
3. Run the user program --> #./user
4. Make sure the time entered is greater than 2seconds [NOTE: The user program takes sleep time in micro seconds - i.e, sleep time > 2000000]

User program forks 2 child process. Each child process creates 5 threads that are synchronised by barrier-1 and 20 threads that are synchronised by barrier-2. After 100 rounds of synchronisation the program exits.







