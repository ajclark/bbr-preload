#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>

int socket(int domain, int type, int protocol);

int socket(int domain, int type, int protocol)
{
  static int (*orig_socket)(int, int, int) = NULL;
  int sockfd = -1;
  char *cong_algorithm = "bbr";
  int slen = strlen(cong_algorithm);

  /* call original function with parameters */
  if(!orig_socket && !(*(void **)(&orig_socket) = dlsym(RTLD_NEXT, "socket"))) {
    errno = EACCES;
  }
  sockfd = (*orig_socket)(domain, type, protocol);

  /* socket must be TCP */
  if((type==SOCK_STREAM)) {
    /* set BBR */
    if (setsockopt(sockfd, IPPROTO_TCP, TCP_CONGESTION, cong_algorithm, slen)<0) {
      dlerror();
    }
  }
  return sockfd;
}
