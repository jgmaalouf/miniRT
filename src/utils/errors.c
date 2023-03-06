/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:41:05 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/06 19:56:52 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

#define RESET "\001\e[0m\002"
#define BOLD "\001\e[1m\002"
#define RED "\001\e[31m\002"

int	inval_input(int type)
{
	const char	*error;

	error = RED BOLD "Error\n" RESET;
	if (type == INVALID_ARGS)
		printf("%s%s\n", error, "Not enough args!");
	if (type == INVALID_FILE)
		printf("%s%s\n", error,
			"File is invalid! Make sure the file extension is '.rt'");
	return (EXIT_FAILURE);
}

int	inval_amount(int type, char *str)
{
	const char	*error;

	error = RED BOLD "Error\n" RESET;
	if (type == MORE)
		printf("%sThere are more %s than required!\n", error, str);
	else if (type == LESS)
		printf("%sThere is an insufficient amount of %s!\n", error, str);
	return (EXIT_FAILURE);
}

void	panic(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}

bool	inval_arg(int type, char *str)
{
	const char	*error;

	error = RED BOLD "Error\n" RESET;
	if (type == RATIO)
		printf("%sThe %s ratio is invalid!\n", error, str);
	else if (type == COORD)
		printf("%sThe coordinates for the %s are invalid!\n", error, str);
	else if (type == ORIENT)
		printf("%sThe orientation vector for the %s is invalid!\n", error, str);
	else if (type == FOV)
		printf("%sThe FOV value for the %s is invalid!\n", error, str);
	else if (type == SIZE)
		printf("%sThe %s is invalid!\n", error, str);
	else if (type == RGB)
		printf("%sThe RGB value for %s is invalid!\n", error, str);
	else if (type == ELEM)
		printf("%sThe element %s is invalid!\n", error, str);
	else if (type == UNKNOWN)
		printf("%sThe %s is unknown!\n", error, str);
	return (false);
}
