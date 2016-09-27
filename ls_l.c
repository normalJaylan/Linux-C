/*	This code achieve the feature "ls -l" of linux in C
 *	@author: Jaylan
 *	date: 2016/9/26
 * */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <memory.h>
#include <time.h>

void output_permission(mode_t mode)
{
	char* perm[8] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};	 // permission (rwx) 

	printf("%s", perm[mode>>6 & 07]);
	printf("%s", perm[mode>>3 & 07]);
	printf("%s ", perm[mode>>0 & 07]);
}

void output_type(mode_t mode)										// type
{
	char type[7] = {'p', 'c', 'd', 'b', '-', 'l', 's'};
	
	printf("%c", type[(mode>>12 & 0xF) / 2]);
}

void output_owner(uid_t uid, gid_t gid)								// owner
{
	struct passwd* user;
	struct group* group;
	user = getpwuid(uid);
	group = getgrgid(gid);

	printf(" %s", user->pw_name);
	printf(" %s ", group->gr_name);
}

void output_time(time_t time)							// time
{
	char buf[256];
	memset(buf, '\0', 256);
	ctime_r(&time, buf);
	buf[strlen(buf) - 1] = '\0';
	printf(" %s ", buf);
}

int main(int argc, char** argv)							// main
{
	DIR* dir;
	struct dirent* ptr;
	struct stat info;

	if (argc < 2)				// if user have not input a file
	{
		printf("usage error!\n");
		exit(EXIT_FAILURE);
	}

	if ((dir = opendir(argv[1])) == NULL)	// if the file doesn't exist
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	
	while ((ptr = readdir(dir)) != NULL)    // display
	{
		if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)   // don't display hide file
			continue;

		stat(ptr->d_name, &info);							// get information of file
		output_type(info.st_mode);         					 // output type
		output_permission(info.st_mode);				   	// output permission	
		printf("%d ", info.st_nlink);						// output number of hard link
		output_owner(info.st_uid, info.st_gid);				// output owner				
		printf("%d ", info.st_size);					// output size
		output_time(info.st_mtime);                         // output time
		printf("%s\n", ptr->d_name);						// output filename
	}
	
	closedir(dir);
	return 0;
}
