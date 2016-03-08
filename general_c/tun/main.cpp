#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdint.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int tun_alloc(char *dev, int dev_size)
{
   struct ifreq ifr;
   int fd, err;

   if ((fd = open("/dev/net/tun", O_RDWR)) < 0)
      return 1;

   memset(&ifr, 0, sizeof (ifr));

   ifr.ifr_flags = IFF_TAP;
   if (*dev) {
      strncpy(ifr.ifr_name, dev, IFNAMSIZ);
   }


   if ((err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0) {
      close(fd);
      return err;
   }
   strncpy(dev, ifr.ifr_name, dev_size);
   return fd;

}

int main(int argc, char **argv)
{

   char dev[20] = "Barco0";
   
   int fd = tun_alloc(dev, sizeof(dev));
   
   char ch;
   scanf("%c", &ch);
   
   return 0;
}
