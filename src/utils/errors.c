/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:41:05 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/11 21:20:52 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "errors.h"
#include "parse.h"

#include <stdio.h>
#include <stdbool.h>

#define RESET "\001\e[0m\002"
#define BOLD "\001\e[1m\002"
#define RED "\001\e[31m\002"

static const char	*error = RED BOLD "Error\n" RESET;

bool	inval_input(int type)
{
	if (type == INVALID_ARGS)
		printf("%s%s\n", error, "Not enough args!");
	if (type == INVALID_FILE)
		printf("%s%s\n", error,
			"File is invalid! Make sure the file extension is '.rt'");
	return (true);
}

bool	inval_amount(int type, char *str)
{
	if (type == MORE)
		printf("%sThere are more %s than required!\n", error, str);
	else if (type == LESS)
		printf("%sThere is an insufficient amount of %s!\n", error, str);
	return (false);
}

void	panic(char *str)
{
	ft_putstr_fd(error, 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
}

void	panic_exit(char *str)
{
	ft_putstr_fd(error, 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}

static char	*get_type_name(uint8_t elem_type)
{
	if (elem_type == g_amb_light)
		return ("ambient light");
	if (elem_type == g_camera)
		return ("camera");
	if (elem_type == g_light)
		return ("light");
	if (elem_type == g_sphere)
		return ("sphere");
	if (elem_type == g_plane)
		return ("plane");
	if (elem_type == g_cylinder)
		return ("cylinder");
	return ("\b");
}

bool	inval_arg(uint8_t error_type, uint8_t elem_type)
{
	char		*elem_name;

	elem_name = get_type_name(elem_type);
	if (error_type == TOK_RATIO)
		printf("%sThe %s ratio is invalid!\n", error, elem_name);
	else if (error_type == TOK_COORD)
		printf("%sThe coordinates for the %s are invalid!\n", error, elem_name);
	else if (error_type == TOK_ORIENT)
		printf("%sThe orientation vector for the %s is invalid!\n", error, elem_name);
	else if (error_type == TOK_FOV)
		printf("%sThe FOV value for the %s is invalid!\n", error, elem_name);
	else if (error_type == TOK_DIAMETER)
		printf("%sThe %s diameter is invalid!\n", error, elem_name);
	else if (error_type == TOK_HEIGHT)
		printf("%sThe %s height is invalid!\n", error, elem_name);
	else if (error_type == TOK_RGB)
		printf("%sThe RGB value for %s is invalid!\n", error, elem_name);
	else
		printf("%sThe element %s is invalid!\n", error, elem_name);
	return (false);
}
