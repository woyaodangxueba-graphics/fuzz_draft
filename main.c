/*this is our main*/
#define _GNU_SOURCE
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "generator.h"

int main (int argc, char *argv[])
{
	//get path from argv
	if (argc != 3) {
       fprintf(stderr,"usage:\t%s -v victimfile(absolutepath)\n", argv[0]);
       exit(0);
    }
    
    char *v = "-v";
    char *dir_path;
    
    if (strcmp(argv[1], v) == 0){
         dir_path = argv[2];
         //fprintf(stderr,"%s\n",dir_path);
        }
    else
    {
    	fprintf(stderr,"invalid arguments\n");
    	fprintf(stderr,"usage:\t%s -v victimfile(absolutepath)\n", argv[0]);
    	exit(0);
    } 
	
	/*******************************************/
	/*******************init()******************/
	/*******************************************/
	//1. figure out memory needed for para_pool and malloc to it
	
	struct para_pool *Pool;
	int files_number = 0;
	
	generator_init(dir_path, &files_number);
	//malloc additional 3 for fd 0,1,2, 100 for "invalid_pool"
	Pool->fd_pool = malloc(sizeof(int)* (files_number + 3 + 100));
	
	//2. generator file descriptors pool
	int fd_index = 0;
	int *fd_index_p = &fd_index;
	generator_fd(Pool, dir_path, fd_index_p);
	
	// loop over remaining fd[] and full them with random numbers
	srand(time(NULL));
	    
	while (fd_index< files_number)
	{
		Pool->fd_pool[fd_index] = rand();
		fd_index++;
	}
	
	/*******************************************/
	/*******************syscall()***************/
	/*******************************************/
	
	int para_1 = rand()%files_number;
	char tmp[32];
	char *para_2 = tmp;
	
	int para_3 = rand()%512;
	fprintf(stdout,"calling sys_read(%d,%x,%d)\n", para_1, (unsigned int)&tmp, para_3);
	
	int ret = 0;
	if (para_1)
	{
		ret = syscall(SYS_read, para_1, para_2, para_3);
		
		if (ret == -1)
		{
		//int errsv = errno;
		fprintf(stdout, "sys_read failed with errno = %d\n", errno);
		}else 
		{
		fprintf(stdout, "sys_read success with %s\n", para_2 );
		}
	}
	


}
