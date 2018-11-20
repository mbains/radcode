#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MEGABYTE 1024*1024

int main(int argc, char *argv[])
{

	char buf [5] = "1234";
	int fd = open("/tmp/binary", O_RDONLY);
	int bytes_read = 0;

	printf("%s\n",buf);
	printf("strlen %lu bytes\n",strlen(buf));
	if(fd)
	{
		if((bytes_read = read(fd, buf, 5)) > 2)
		{
			printf("read %d bytes\n",bytes_read);
			printf("strlen %lu bytes\n",strlen(buf));
                        printf("%s\n",buf);
		}
		close(fd);	
	}else {
	
	}

        
}
