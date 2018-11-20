

/* 
 * File:   eb_passthru.cpp
 * Author: manny
 *
 * Created on April 17, 2018, 10:26 AM
 */

#include <cstdlib>
#include <string.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <map>


#define SERIAL_BUFFER_EVENT
using namespace std;

static struct event_base *base;
static bufferevent * serial_bev = NULL;
static std::map<int, bufferevent*> client_num_to_bf;

static const char MESSAGE[] = "Hello, World!\n";

static const int PORT = 9995;

static void listener_cb(struct evconnlistener *, evutil_socket_t,
    struct sockaddr *, int socklen, void *);

static void conn_writecb(struct bufferevent *, void *);
static void conn_readcb(struct bufferevent *, void *);
static void serial_writecb(struct bufferevent *, void *);
static void serial_readcb(struct bufferevent *, void *);
static void conn_eventcb(struct bufferevent *, short, void *);
static void signal_cb(evutil_socket_t, short, void *);



static void
fifo_read(evutil_socket_t fd, short event, void *arg)
{
	char buf[255];
	int len;
	struct event *ev = static_cast<struct event *> (arg);


	fprintf(stderr, "fifo_read called with fd: %d, event: %d, arg: %p\n",
	    (int)fd, event, arg);

	len = read(fd, buf, sizeof(buf) - 1);

	if (len > 0) {
        buf[len] = '\0';
        fprintf(stdout, "Read: %s\n", buf);
	}

}


/**
 * Add file descriptor fd to event_base base 
 * @param base
 * @param fd
 * @return event *
 */
event * make_ev_handle(event_base * base, int fd, short flags, event_callback_fn fn){
   event * evt = event_new(base, fd, flags|EV_PERSIST, fn,
                           event_self_cbarg());
   return evt;
}

int open_serial(const char * port)
{
    struct termios options;
    int port_fd = open(port, O_RDWR | O_NONBLOCK | O_NOCTTY);
    if(port_fd > 0){
        if( tcgetattr(port_fd, &options) != -1) {
            
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;
            options.c_cflag &= ~CSIZE;
            options.c_cflag |= CS8;
            options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
            
            cfsetispeed(&options, B115200);
            if(tcsetattr(port_fd, TCSANOW, &options) == -1) {
                perror("tcsetattr");
            } else
            {
                return port_fd; 
            }
        } else {
            perror("tcgetattr");
        }
    }
    
    return -1;
}


/*
 * 
 */
int main(int argc, char** argv) {

	struct evconnlistener *listener;
	struct event *signal_event;
    
    struct sockaddr_in sin;

	base = event_base_new();
	if (!base) {
		fprintf(stderr, "Could not initialize libevent!\n");
		return 1;
	}

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);

	listener = evconnlistener_new_bind(base, listener_cb, (void *)base,
	    LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
	    (struct sockaddr*)&sin,
	    sizeof(sin));

	if (!listener) {
		fprintf(stderr, "Could not create a listener!\n");
		return 1;
	}

	signal_event = evsignal_new(base, SIGINT, signal_cb, (void *)base);

	if (!signal_event || event_add(signal_event, NULL)<0) {
		fprintf(stderr, "Could not create/add a signal event!\n");
		return 1;
	}
    
    int serialfd = open_serial("/dev/ttyUSB0");
    
    if(serialfd < 1){
        printf("serial port failed\n");
        return -1;
    }

#ifdef SERIAL_BUFFER_EVENT
    serial_bev = bufferevent_socket_new(base, serialfd, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(serial_bev, serial_readcb, serial_writecb, conn_eventcb, NULL);
    bufferevent_enable(serial_bev, EV_WRITE);
	bufferevent_enable(serial_bev, EV_READ|EV_PERSIST);
#else
    auto evfifo = event_new(base, serialfd, EV_READ|EV_PERSIST, fifo_read, event_self_cbarg());
    event_add(evfifo, NULL);
#endif
    
	event_base_dispatch(base);

	evconnlistener_free(listener);
	event_free(signal_event);
	event_base_free(base);
    close(serialfd);

	printf("done\n");
    return 0;
}


static void
listener_cb(struct evconnlistener *listener, evutil_socket_t fd,
    struct sockaddr *sa, int socklen, void *user_data)
{
    printf("listener_cb called\n");
	struct event_base *base = static_cast <event_base *>(user_data);
	struct bufferevent *bev;

	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev) {
		fprintf(stderr, "Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}
    static int connection_num = 0;
    int * copy_num = new int();
    client_num_to_bf[connection_num] = bev;
    *copy_num = connection_num++;
	bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_eventcb, copy_num);
	bufferevent_enable(bev, EV_WRITE);
	bufferevent_enable(bev, EV_READ);

	bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
}

static void
conn_writecb(struct bufferevent *bev, void *user_data)
{
	struct evbuffer *output = bufferevent_get_output(bev);
	if (evbuffer_get_length(output) == 0) {
		printf("flushed answer\n");
		//bufferevent_free(bev);
	}
}

static void serial_writecb(struct bufferevent *bev, void *user_data)
{
	struct evbuffer *output = bufferevent_get_output(bev);
	if (evbuffer_get_length(output) == 0) {
		printf("serial write done\n");
		//bufferevent_free(bev);
	}
}

static void serial_readcb(struct bufferevent *bev, void *user_data)
{
    int count = 0;
   
    printf("%s called\n", __func__);

    char c[512];
    memset(c, 0, 512);
    if((count = bufferevent_read(bev, c, 511)) > 0){
        printf("<< read %d bytes %s\n", count, c);
        for(auto& kv: client_num_to_bf) {
            bufferevent * client_bev = kv.second;
            bufferevent_write(client_bev, c, count);
        }
        
    }
}

static void
conn_readcb(struct bufferevent *bev, void *user_data)
{
    int count = 0;
    int connection_num = *(static_cast<int *>(user_data));
    printf("%d %s called\n", connection_num, __func__);

    char c[512];
    memset(c, 0, 512);
    if((count = bufferevent_read(bev, c, 511)) > 0){
        printf(">> writing %d bytes %s\n", count, c);
        bufferevent_write(serial_bev, c, count);
        //bufferevent_write(bev, c, count);
    }
}

static void
conn_eventcb(struct bufferevent *bev, short events, void *user_data)
{
	if (events & BEV_EVENT_EOF) {
        int * num = static_cast<int *> (user_data);
		printf("Connection closed.\n");
        auto it = client_num_to_bf.find(*num);
        client_num_to_bf.erase(it);
        delete num;
	} else if (events & BEV_EVENT_ERROR) {
		printf("Got an error on the connection: %s\n",
		    strerror(errno));/*XXX win32*/
	}
	/* None of the other events can happen here, since we haven't enabled
	 * timeouts */
	bufferevent_free(bev);
}

static void
signal_cb(evutil_socket_t sig, short events, void *user_data)
{
	struct event_base *base = static_cast<event_base *>(user_data);
	struct timeval delay = { 2, 0 };

	printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");

	event_base_loopexit(base, &delay);
}

