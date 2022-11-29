#ifndef  HANDLER_H
#define  HANDLER_H
#include <winsock2.h>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>

void* connection_handler(void*);

#endif // ! _AF_NET_
