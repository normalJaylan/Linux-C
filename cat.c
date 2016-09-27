#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char** argv)
{
	FILE* file;
	char line[1000] = {0};
	char type[7] = {'p', 'c', 'd', 'b', '-', 'l', 's'};

	struct stat info;

	if (argc < 2)
	{
		printf("usage error!");
		exit(EXIT_FAILURE);
	}

	if ((file = fopen(argv[1], "r")) == NULL) 
	{
		perror("openfile");
		exit(EXIT_FAILURE);
	}

	stat(argv[1], &info);

	if (type[(info.st_mode>>12 & 0xF) / 2] == 'd')
	{
		printf("This can not read\n");
		exit(EXIT_FAILURE);
	}

	while (!feof(file))
	{
		memset(line, 0, sizeof(line));
		fgets(line, sizeof(line) - 1, file);
		printf("%s", line);
	}

	fclose(file);
	printf("\n");
	
	return 0;
}
