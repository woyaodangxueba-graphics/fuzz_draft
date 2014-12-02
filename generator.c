#include <dirent.h> 
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "generator.h"
// struct link *fds;
// fds = malloc(sizeof(struct link));
// 
// int determine_num()
// {
// 
// }


// helper function to determine whether a file is a regular file or a directory 
int determine_dir(char direct[])
{
	struct stat status;

	stat(direct, &status);

	if (status.st_mode & S_IFDIR) // is a directory file.
		return 0;
	if (status.st_mode & S_IFREG) // is a regular file.
		return 1;
	return -1;
}

//recursively loop a absolute path, open all files and returns file descriptors to pool->fd_pool.
void generator_fd(struct para_pool *pool, char *direct, int *index)
{
	int regular = 0;
	int count, i;
	char *abs_dir;
	DIR *d;
	struct dirent *dir;

	d = opendir(direct);

	if (d != NULL)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
			{
				count = 0;
				for(i = 0; dir->d_name[i] != '\0'; i++)
					count++;

				abs_dir = (char*)malloc((count + 2) * sizeof(char));

				strcpy(abs_dir, direct);
				strcat(abs_dir, "/");
				strcat(abs_dir, dir->d_name);

				pool->fd_pool[*index] = open(abs_dir, O_RDONLY);
				(*index)++;

				regular = determine_dir(abs_dir);

				if (regular == 0)
					generator_fd(pool, abs_dir, index);
			}
		}
	}
}

/* Generate an array of directories for testing. */
void generator_dir(struct para_pool *pool, char *direct, int *index)
{
	int regular;
	int count, i;
	char *abs_dir;
	DIR *d;
	struct dirent *dir;

	d = opendir(direct);

	if(d != NULL)
	{
		while((dir = readdir(d)) != NULL)
		{
			if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
			{
				count = 0;
				for(i = 0; dir->d_name[i] != '\0'; i++)
					count++;

				abs_dir = (char*)malloc((count + 2) * sizeof(char));

				strcpy(abs_dir, direct);
				strcat(abs_dir, "/");
				strcat(abs_dir, dir->d_name);

				pool->dirs_pool[*index] = abs_dir;
				(*index)++;

				regular = determine_dir(abs_dir);

				if (regular == 0)
<<<<<<< HEAD
					generator_dir(pool, abs_dir, index);
=======
					generator_dir(abs_dir, index);
>>>>>>> FETCH_HEAD
			}
		}
	}
}

//recursively loop a absolute path, count all files.
void generator_init(char *direct, int *files_number)
{
	int regular = 0;
	char *abs_dir;
	int count, i;
	DIR *d;
	struct dirent *dir;

	d = opendir(direct);

	if (d != NULL)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
			{
				count = 0;
				for(i = 0; dir->d_name[i] != '\0'; i++)
					count++;

				abs_dir = (char*)malloc((count + 2) * sizeof(char));

				strcpy(abs_dir, direct);
				strcat(abs_dir, "/");
				strcat(abs_dir, dir->d_name);

				(*files_number)++;

				regular = determine_dir(abs_dir);

				if (regular == 0)
					generator_init_fd(abs_dir, files_number);
			}
		}
	}
}

void generator_init_fd(char *direct, int *index)
{
	int regular = 0;
	int count, i;
	char *abs_dir;
	DIR *d;
	struct dirent *dir;

	d = opendir(direct);

	if (d != NULL)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
			{
				count = 0;
				for(i = 0; dir->d_name[i] != '\0'; i++)
					count++;

				abs_dir = (char*)malloc((count + 2) * sizeof(char));

				strcpy(abs_dir, direct);
				strcat(abs_dir, "/");
				strcat(abs_dir, dir->d_name);

				//pool->fd_pool[*index] = open(abs_dir, O_RDONLY);
				(*index)++;

				regular = determine_dir(abs_dir);

				if (regular == 0)
					generator_init_fd(abs_dir, index);
			}
		}
	}
}
void generator_mod()
{

}
