/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:02:32 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/12 20:09:51 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include "errors.h"

#include <stdlib.h>

#define RESET "\001\e[0m\002"
#define BOLD "\001\e[1m\002"
#define RED "\001\e[31m\002"

static const char	*error = RED BOLD "Error\n" RESET;

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
