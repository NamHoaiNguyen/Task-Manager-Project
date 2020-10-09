#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "../kernel_modules/task-list.h"

#define filename  "/dev/procid"

struct task_info *test_info;
struct task_info *test_write;
int count = 0;
int main()
{
	int fd, i = 0;
	fd = open(filename, O_RDWR);
	if (fd < 0) {
		perror("open failed\n");
		return -1;
	}

	if (ioctl (fd, IOCTL_NUMBER, &count) < 0) {
		return -1;
	}

	printf("%d\n",count);


	int num_byte;
	char test[50];
	 if ((num_byte = read(fd, test, 50)) < 0) {
                 perror("read failed\n"); 
                 return -1;
	 }

	printf("%d\n", num_byte);

	return 0;
}
