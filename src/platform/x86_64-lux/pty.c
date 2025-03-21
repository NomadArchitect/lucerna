/*
 * lucerna - an implementation of the standard C library
 * Omar Elghoul, 2024
 *
 * Platform-Specific Code for x86_64 lux
 */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <fcntl.h>

/* ioctl commands here are specific to the luxOS pty driver and will not work
 * on any other terminal implementation */

#define PTY_GET_SECONDARY       (0x10 | IOCTL_OUT_PARAM)
#define PTY_GRANT_PT            0x20
#define PTY_UNLOCK_PT           0x30
#define PTY_TTY_NAME            (0x40 | IOCTL_OUT_PARAM)

#define PTY_SET_FOREGROUND      (0xF0 | IOCTL_IN_PARAM)
#define PTY_GET_FOREGROUND      (0x100 | IOCTL_OUT_PARAM)

static char ptyname[128];
static char ttybuf[128];

/* posix_openpt(): creates and opens a new pseudo-terminal
 * params: flags - open flags to be used in the primary descriptor
 * returns: file descriptor of the primary, -1 on error and errno set
 */

int posix_openpt(int flags) {
    return open("/dev/ptmx", flags, 0);
}

/* ptsname(): returns the name of the secondary pseudo-terminal
 * params: fd - file descriptor of the primary
 * returns: pointer to the secondary file name, NULL on error
 */

char *ptsname(int fd) {
    if(ptsname_r(fd, ptyname, sizeof(ptyname))) return NULL;
    return ptyname;
}

/* ptsname_r(): returns the name of the secondary pseudo-terminal in a buffer
 * note: this function is NOT in the POSIX standard, but it is implemented by
 * Linux and OpenBSD and frankly it is quite useful and more secure
 * 
 * params: fd - file descriptor of the primary
 * params: buf - destination buffer
 * params: bufsz - buffer size
 * returns: zero on success, error code on error
 */

int ptsname_r(int fd, char *buf, size_t bufsz) {
    unsigned long id;
    if(!ioctl(fd, PTY_GET_SECONDARY, &id)) {
        snprintf(buf, bufsz, "/dev/pts%ld", id);
        return 0;
    }

    return -1;      // errno set by ioctl()
}

/* grantpt(): changes the mode and owner of the secondary pseudo-terminal
 * the owner will be set to the UID of the caller and the permissions
 * will be set to rw--w----
 *
 * params: fd - file descriptor of the primary
 * returns: zero on success, -1 on error and errno set
 */

int grantpt(int fd) {
    return ioctl(fd, PTY_GRANT_PT, 0);
}

/* unlockpt(): unlocks the secondary pseudo-terminal so that can be opened
 * params: fd - file descriptor of the primary
 * returns: zero on success, -1 on error and errno set
 */

int unlockpt(int fd) {
    return ioctl(fd, PTY_UNLOCK_PT, 0);
}

/* ttyname_r(): thread-safe function to return the name of a tty
 * params: fd - file descriptor of the secondary
 * params: buf - buffer to store file name
 * params: bufsz - buffer size
 * returns: zero on success
 */

int ttyname_r(int fd, char *buf, size_t bufsz) {
    unsigned long id;
    if(!ioctl(fd, PTY_TTY_NAME, &id)) {
        snprintf(buf, bufsz, "/dev/pts%d", id);
        return 0;
    } else {
        return errno;
    }
}

/* ttyname(): non-thread-safe version of ttyname_r()
 * params: fd - file descriptor of the secondary
 * returns: pointer to secondary path, NULL on error
 */

char *ttyname(int fd) {
    if(ttyname_r(fd, ttybuf, 127)) return NULL;
    else return ttybuf;
}

/* tcgetpgrp(): returns the PID of a terminal's process group
 * params: fd - file descriptor of the terminal
 * returns: process group ID
 */

pid_t tcgetpgrp(int fd) {
    unsigned long pid;
    if(ioctl(fd, PTY_GET_FOREGROUND, &pid)) return -1;
    return (pid_t) pid;
}

/* tcsetpgrp(): sets the PID of a terminal's process group
 * params: fd - file descriptor of the terminal
 * params: pgrp - process group ID
 * returns: zero on success
 */

int tcsetpgrp(int fd, pid_t pgrp) {
    signed long pid = (signed long) pgrp;
    return ioctl(fd, PTY_SET_FOREGROUND, (unsigned long) pid);
}
