#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <math.h>

#include "../kernel_modules/task-list.h"
#include "test_proc.h"


struct task_info *test_info;
struct task_info *test_write;
int count = 0;
int main()
{
	int fd, num_byte, prev_count; 
	int i = 0;
	double mem_per;
	unsigned long total_mem = (1UL << physical_memory);
	printf("%lu\n", total_mem);

	fd = open(filename, O_RDWR);
	if (fd < 0) {
		perror("open failed\n");
		return -1;
	}
	
	while (1) {
	if (ioctl (fd, IOCTL_NUMBER, &count) < 0) {
		return -1;
	}

	
	printf("%d\n",count);



	test_info = (struct task_info *)malloc(count * sizeof(struct task_info));
	if ((num_byte = read(fd, test_info, count * sizeof(struct task_info))) < 0) {

                 perror("read failed\n"); 
                 return -1;
	}

	printf("%d\n", num_byte);

	for (i = 0; i < count; i++) {
		if (test_info[i].vma_size / total_mem > 1) {
			mem_per = 100;	
			
		}
		else if (test_info[i].vma_size == 0) {
			mem_per = 0;
		}
		else {
			mem_per = (double)(test_info[i].vma_size) / (double)(total_mem) * 100; 
		
		}
		printf("Process : %s\t, PID: %d\t, start_time :%lu\t, total_time: %lu\t, vma_size: %lu\t, memory:%.6f\n"
				, test_info[i].comm, test_info[i].pid,test_info[i].start_time
				, test_info[i].total_time, test_info[i].vma_size, mem_per);
	}
	
	prev_count = count;	

	free(test_info);


	sleep(1);
	}
	return 0;
}
