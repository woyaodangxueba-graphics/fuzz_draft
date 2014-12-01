#include <dirent.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
// struct node
// {
// 	int val;
// 	struct node *next;
// };

// struct link
// {
// 	struct node *head;
// 	struct node *last;
// };

struct para_pool
{
	int *fd_pool;
	int *mode;
};

void generator_init(char *direct, int *files_number);
void generator_fd(struct para_pool *pool, char *direct, int *index);
void generator_mod();
