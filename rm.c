#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("usage error!\n");
		exit(EXIT_FAILURE);
	}

	unlink(argv[1]);
}
