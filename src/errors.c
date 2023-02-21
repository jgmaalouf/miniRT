#include "errors.h"

int	invalid_input(int type)
{
	if (type == INVALID_ARGS)
		printf("Error\n%s\n", "Not enough args!");
	return(EXIT_FAILURE);
}

int	too_much(char *str)
{
	printf("Error\nThere are more %s than required!\n", str);
	return(EXIT_FAILURE);
}

int	too_little(char *str)
{
	printf("Error\nThere are not enough %s than required!\n", str);
	return(EXIT_FAILURE);
}

void	panic(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}
