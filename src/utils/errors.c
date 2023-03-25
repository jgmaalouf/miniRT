/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:41:05 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/25 22:04:35 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "errors.h"
#include "parse.h"

#include <stdio.h>
#include <stdbool.h>

#define RESET "\001\e[0m\002"
#define BOLD "\001\e[1m\002"
#define RED "\001\e[31m\002"

static const char	*g_error = RED BOLD "\tError\n" RESET;

bool	inval_input(int type)
{
	if (type == INVALID_ARGS)
		printf("%s%s\n", g_error, "Not enough args!");
	if (type == INVALID_FILE)
		printf("%s%s\n", g_error,
			"File is invalid! Make sure the file extension is '.rt'");
	return (true);
}

bool	inval_amount(int type, char *str)
{
	if (type == MORE)
		printf("%sThere are more %ss than required!\n", g_error, str);
	else if (type == LESS)
		printf("%sThere is an insufficient amount of %ss!\n", g_error, str);
	return (false);
}

void	inval_arg(uint8_t error_type, char *elem_name, size_t line)
{
	size_t	num_token;
	size_t	i;

	printf("%lu:%s", line, g_error);
	if (error_type == (uint8_t)0)
	{
		printf("\tUnexpected character(s)!\n");
		return ;
	}
	num_token = sizeof(p) / sizeof(p[0]);
	i = 0;
	while (i < num_token)
	{
		if (error_type & p[i].token)
			printf(p[i].error_message, elem_name);
		i++;
	}
	return ;
}
