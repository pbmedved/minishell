#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void		handler_sigint(int sig)
{
	char	c;
	if (sig != SIGINT)
		return ;
	else
	{
		printf("\nYou want to quit? (y/n):");
		while ((c = getchar()) != 'y')
			return ;
		exit (0);
	}

}

void		handler_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("Save core dump\n");
		exit (98);
	}
}

int 		main()
{
	int		i = 0;
	char *str;

	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, handler_sigquit);
	// while(read(0, str, 1))
	// 	printf("%s", str);
	while (1)
	{
		printf("You can exit the program using Ctrl + C\n");
		while (i < 48)
		{
			printf("\b");
			i++;
		}
	}
	return (0);
}