#include "./info_sys/info_sys.h"
#include "./test/test_proc.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(int argc, char **argv)
{
	int sel;
	sscanf(argv[1], "%d", &sel);
	printf("Select option: %d\n", sel);

	if(sel == 1)
	{
		display_sys();
	}
	else
	{
	}
}
