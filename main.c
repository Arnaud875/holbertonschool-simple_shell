#include <stdio.h>
#include "main.h"

int main(void)
{
	char *input;
	while (1)
	{
		input = input_user();
		printf("%s", input);
	}
	return (0);
}
