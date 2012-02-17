#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>

#define MAXEVENTS 64
static int make_socket_non_blocking(int sfd)
{
    int flags, s;
    flags = fcntl(sfd, F_GETFD, 0);
    if(flags==-1) 
    {
        perror("fcntl");
        return -1;
    }
    flags |= O_NONBLOCK;
    s = fcntl(sfd, F_SETFL, flags);
    if(s == -1)
    {
        perror("fcntl");
        return -1;
    }
    
    return 0;
}

static int create_and_bind(char *port) 
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int err, sfd;
    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    err = getaddrinfo(NULL, port, &hints, &result);
    if(err != 0)
    {
        fprintf(stderr, "getaddrinfo failed %s\n", gai_strerror(err));
        return -1;
    }
    
    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if(sfd == -1)
            continue;
        
        err = bind(sfd, rp->ai_addr, rp->ai_addrlen);
        if(err == 0)
        {
            break;
        }
        close(sfd);
    }
    
    freeaddrinfo(result);
    return sfd;
}

int main(int argc, char *argv[])
{
    int serverFD, err;
    int epollFD;
    struct epoll_event event;
    struct epoll_event *events;

    if(argc != 2)
    {
        fprintf(stderr, "usage: %s [port]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    serverFD = create_and_bind(argv[1]);
    if(serverFD == -1)
        abort();
    
    err = make_socket_non_blocking(serverFD);
    if(err == -1)
    {
        abort();
    }
    
    err = listen(serverFD, SOMAXCONN);
    if(err == -1)
    {
        perror("listen");
        abort();
    }
    epollFD = epoll_create1(0);
    if(epollFD == -1)
    {
        perror("epoll_create");
        abort();
    }
    
    event.data.fd = serverFD;
    event.events = EPOLLIN | EPOLLET;
    err = epoll_ctl(epollFD, EPOLL_CTL_ADD, serverFD, &event);
    if(err == -1)
    {
        perror("epoll_ctl");
        abort();
    }
    
    events = (epoll_event *)calloc(sizeof(event), MAXEVENTS);
    
    while(1)
    {
        int n, i;
        n = epoll_wait(epollFD, events, MAXEVENTS, -1);
        for(i = 0; i < n; i++)
        {
            if( (events[i].events & EPOLLERR) ||
                (events[i].events & EPOLLHUP) ||
                (!events[i].events & EPOLLIN))
            {
                fprintf(stderr, "epoll error\n");
                close(events[i].data.fd);
                continue;
            }
            else if(serverFD == events[i].data.fd)
            {
                while(1)
                {
                    struct sockaddr in_addr;
                    struct sockaddr *myaddr;
                    socklen_t in_len;
                    int infd;
                    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
                    
                    in_len = sizeof in_addr;
                    infd = accept(serverFD, &in_addr, &in_len);
                    if(infd == -1)
                    {
                        if((errno == EAGAIN ||
                            errno == EWOULDBLOCK ))
                        {
                            break;
                        }
                        else
                        {
                            perror("accept");
                            break;
                        }
                    }
                    
                    err = getnameinfo(&in_addr, in_len, 
                                        hbuf,  sizeof(hbuf), 
                                        sbuf, sizeof(sbuf),
                                        NI_NUMERICHOST | NI_NUMERICSERV);
                    
                    if(err == 0)
                    {
                        printf("Accepted connection on descriptor %d"
                                "host = %s, port = %s)\n", infd,  hbuf, sbuf);
                    }
                    
                    err = make_socket_non_blocking(infd);
                    if(err == -1)
                        abort();
                    
                    event.data.fd = infd;
                    event.events = EPOLLIN | EPOLLET;
                    err = epoll_ctl(epollFD, EPOLL_CTL_ADD, infd, &event);
                    if(err == -1)
                    {
                        perror("epoll_ctl");
                        abort();
                    }
                }
                continue;
            }
            else
            {
                
                int done = 0;
                while(1)
                {
                    ssize_t count;
                    char buf[512];
                    count = read(events[i].data.fd, buf, sizeof(buf));
                    if(count == -1)
                    { 
                        printf("read -1\n");
                        if(errno != EAGAIN)
                        {
                            perror("read");
                            done = 1;
                            break;
                        }
                        break;
                    }
                    else if( count == 0) {
                        done = 1;
                        break;
                    }
                    err = write(1, buf, count);
                    if(err == -1)
                    {
                        perror("write");
                        abort();
                    }
                    
                }
                
                if(done)
                {
                    printf("Closing connection on descriptor %d\n",
                                    events[i].data.fd);
                    close(events[i].data.fd);
                }
            }
        }
    }
    
    free(events);
    close(serverFD);
    return 0;

}
