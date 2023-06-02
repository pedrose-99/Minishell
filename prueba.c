#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

int main()
{
	int i;
	int ancla;

	i = 5;
	ancla = i--;

	printf("%d, %d", ancla, i);


}