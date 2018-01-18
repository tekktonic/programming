#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

enum requestmeth
{
    GET,
};


enum responses
{
    HTTP_OK,
    HTTP_BADREQ,
    HTTP_NOTFOUND,
};

const char *responses[] = {
    "HTTP/1.1 200 OK",
    "HTTP/1.1 400 Bad Request",
    "HTTP/1.1 404 Not Found"
};

void reaper(int signal)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

void cleanup(int sig)
{
    shutdown(control_sock, SHUT_RDWR);
    close(control_sock);
}

int swrite(int fd, char *string)
{
    size_t len = strlen(string);

    return write(fd, string, len);
}

void make_request(int socket, enum responses res_type, char *file)
{
    const char *fourohoh = "400 - Bad Request";
    const char *httpver = "HTTP/1.1";

    const char *server = "tthttpd/0.1";
    switch (res_type)
    {
    case HTTP_BADREQ:
        
        
    }
}
void handle(int socket)
{
    char linebuf[64];
    linebuf = read(socket, linebuf, 63);
    linebuf[63] = "\0";
    if (!(linebuf[0] == 'G' && linebuf[1] == 'E' && linebuf[2] == 'T'))
    {
        
    }
}

int main(void)
{
    int control_sock;
    struct addrinfo *result;
    struct addrinfo addhint = {.ai_family=AF_UNSPEC,
                               .ai_socktype=SOCK_STREAM,
                               .ai_flags=AI_PASSIVE};
    getaddrinfo(NULL, "8080", &addhint, &result);

    control_sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    struct sigaction sint;
    sint.sa_handler = cleanup;
    sigemptyset(&sint.sa_mask);
    sint.sa_flags = SA_RESTART;
    sigation(SIGCHLD, &sint, NULL);

    while (1)
    {
        int connfd = accept(control_sock, (struct sockaddr*)NULL, NULL);
        if (fork() == 0)
        {
            close(control_sock);
            handle(connfd);
        }
    }
}
