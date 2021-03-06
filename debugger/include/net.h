// golden
// 6/12/2018
//

#ifndef _NET_H
#define _NET_H

#include <ps4.h>
#include "errno.h"

#define NET_MAX_LENGTH      8192

// I would like to move away from the stupid sony wrapper functions
// They do not always return what I expect and I want to use straight syscalls

#define FD_SETSIZE 1024
typedef unsigned long fd_mask;

typedef struct {
	unsigned long fds_bits[FD_SETSIZE / 8 / sizeof(long)];
} fd_set;

#define FD_ZERO(s) do { int __i; unsigned long *__b=(s)->fds_bits; for(__i=sizeof (fd_set)/sizeof (long); __i; __i--) *__b++=0; } while(0)
#define FD_SET(d, s)   ((s)->fds_bits[(d)/(8*sizeof(long))] |= (1UL<<((d)%(8*sizeof(long)))))
#define FD_CLR(d, s)   ((s)->fds_bits[(d)/(8*sizeof(long))] &= ~(1UL<<((d)%(8*sizeof(long)))))
#define FD_ISSET(d, s) !!((s)->fds_bits[(d)/(8*sizeof(long))] & (1UL<<((d)%(8*sizeof(long)))))

int net_select(int fd, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

int net_send_data(int fd, void *data, int length);
int net_recv_data(int fd, void *data, int length, int force);
int net_send_status(int fd, uint32_t status);

#endif
