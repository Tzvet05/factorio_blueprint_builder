// Factorio blueprint builder - source code

#include "blueprint_builder.h"

void	puterr(char *str1, char *str2)
{
	write(2, EXECUTABLE_NAME, strlen(EXECUTABLE_NAME));
	write(2, " : ", 3);
	write(2, str1, strlen(str1));
	if (str2 != NULL)
	{
		write(2, " : ", 3);
		write(2, str2, strlen(str2));
	}
	write(2, "\n", 1);
}
