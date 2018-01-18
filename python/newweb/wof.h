#ifdef WOF_H
#define WOF_H

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct WOFConnection_struct
{
    sockaddr_in sock;

    const char *server;
}WOFConnection_struct;

typedef struct WOFConnection_struct *WOFConnection;

unsigned long WOF_Size(WOFConnection conn, const char *file);

const char **WOF_List(WOFConnection conn, const char *directory);

const char *WOF_GetN(WOFConnection conn, const char *file, void callback(), void *arg);

void WOF_Get(WOFConnection conn, const char *file);

const char *WOF_GetToStringN(WOFConnection conn, const char *file);

FILE *WOF_GetToFile(WOFConnection conn, const char *file);
#endif
