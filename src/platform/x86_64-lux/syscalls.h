/*
 * lucerna - an implementation of the standard C library
 * Omar Elghoul, 2024
 *
 * Platform-Specific Code for x86_64 lux
 */

#pragma once

// lux microkernel system call indexes

#include <stdint.h>

/* Group 1: Processes, Threads, and Users */

#define SYSCALL_EXIT            0
#define SYSCALL_FORK            1
#define SYSCALL_YIELD           2
#define SYSCALL_WAITPID         3
#define SYSCALL_EXECVE          4
#define SYSCALL_EXECRDV         5
#define SYSCALL_GETPID          6
#define SYSCALL_GETTID          7
#define SYSCALL_GETUID          8
#define SYSCALL_GETGID          9
#define SYSCALL_SETUID          10
#define SYSCALL_SETGID          11
#define SYSCALL_MSLEEP          12
#define SYSCALL_GETTIMEOFDAY    13
#define SYSCALL_GETPGRP         14
#define SYSCALL_SETPGRP         15

/* Group 2: File System Manipulation */

#define SYSCALL_OPEN            16
#define SYSCALL_CLOSE           17
#define SYSCALL_READ            18
#define SYSCALL_WRITE           19
#define SYSCALL_LSTAT           20
#define SYSCALL_FSTAT           21
#define SYSCALL_LSEEK           22
#define SYSCALL_CHOWN           23
#define SYSCALL_CHMOD           24
#define SYSCALL_LINK            25
#define SYSCALL_UNLINK          26
#define SYSCALL_SYMLINK         27
#define SYSCALL_READLINK        28
#define SYSCALL_UMASK           29
#define SYSCALL_MKDIR           30
#define SYSCALL_UTIME           31
#define SYSCALL_CHROOT          32
#define SYSCALL_CHDIR           33
#define SYSCALL_GETCWD          34
#define SYSCALL_MOUNT           35
#define SYSCALL_UMOUNT2         36
#define SYSCALL_FCNTL           37
#define SYSCALL_OPENDIR         38
#define SYSCALL_CLOSEDIR        39
#define SYSCALL_READDIR_R       40
#define SYSCALL_SEEKDIR         41
#define SYSCALL_TELLDIR         42
#define SYSCALL_FSYNC           43
#define SYSCALL_STATVFS         44
#define SYSCALL_FSTATVFS        45

/* Group 3: Interprocess Communication */

#define SYSCALL_SOCKET          46
#define SYSCALL_CONNECT         47
#define SYSCALL_BIND            48
#define SYSCALL_LISTEN          49
#define SYSCALL_ACCEPT          50
#define SYSCALL_RECV            51
#define SYSCALL_SEND            52
#define SYSCALL_KILL            53
#define SYSCALL_SIGACTION       54
#define SYSCALL_SIGRETURN       55
#define SYSCALL_SIGPROCMASK     56

/* Group 4: Memory Management */

#define SYSCALL_SBRK            57
#define SYSCALL_MMAP            58
#define SYSCALL_MUNMAP          59
#define SYSCALL_MSYNC           60

/* Group 5: Driver I/O Functions */

#define SYSCALL_IOPERM          61
#define SYSCALL_IRQ             62
#define SYSCALL_IOCTL           63
#define SYSCALL_MMIO            64
#define SYSCALL_PCONTIG         65
#define SYSCALL_VTOP            66

uint64_t luxSyscall(uint64_t request, uint64_t p0, uint64_t p1, uint64_t p2, uint64_t p3);
