#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char *buffer;
	size_t len = 256;
	int readc = 0;

	
	while (readc != -1)
	{
		printf("currentuser$: ");
		readc = getline(&buffer, &len, stdin);
		if (readc != -1)
			printf("The count is: %d\nThe characters inputed are: %s", readc, buffer);
		else
			printf("\n");
	}
	free(buffer);
	return (0);
}
