#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_empty(char *b)
{
	if (!b)
		return (1);
	else if (strlen(b) == 0)
		return (1);
	else
		return (0);
}

int found_newline_s(char *b)
{
	while (*b)
	{
		if (*b == '\n')
			return (1);
		b++;
	}
	return (0);
}


int main ()
{
	ssize_t res = -2;
	char *b;

	b = (char *)calloc(5, sizeof(char));
	while (1)
	{
		res = read(0, b, 5);
		if (is_empty(b) && res == 0)
			exit(0);
		else if (!is_empty(b) && found_newline_s(b))
		{
			printf("Processing...\n");
			b = NULL;
		}
		else if (!is_empty(b) && !found_newline_s(b))
			continue;
	}
	return (0);
}