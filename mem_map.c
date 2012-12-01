 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <fcntl.h>

 #define REGISTERINFO "/proc/sys_reg"
 #define BUFSIZE  4096

 static char buf[BUFSIZE];
 static unsigned long addr;

 #define FILE_TO_BUF(filename, fd) do{	\
	static int local_n;	\
	if (fd == - 1 && (fd = open(filename, O_RDONLY)) == - 1) {	\
	fprintf(stderr, "Open /proc/register file failed! \n");	\
	fflush(NULL);	\
	_exit(102);	\
	}	\
	lseek(fd, 0L, SEEK_SET);	\
	if ((local_n = read(fd, buf , sizeof buf -  1)) < 0) {	\
	perror(filename);	\
	fflush(NULL);	\
	_exit(103);	\
	}	\
	buf [local_n] = 0;	\
 }while(0)



 int main()
 {
	unsigned long tmp;
	tmp = 0x12345678;
	static int cr_fd = - 1;

	asm("movl %ebp, %ebx\n movl %ebx, addr");

	printf("\n%%ebp:0x%08lX\n", addr);
	printf("tmp address:0x%08lX\n", &tmp);
	FILE_TO_BUF(REGISTERINFO, cr_fd);

	printf("%s", buf );

	while(1);

	return 0;
 }

