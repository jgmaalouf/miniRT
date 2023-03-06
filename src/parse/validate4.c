/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:54 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/06 19:53:06 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_isnumber(char *s)
{
	if (*s == '+' || *s == '-')
		s++;
	while (ft_isdigit(*s++))
		if (*s == '\0' || ft_isspace(*s) || *s == ',')
			return (1);
	return (0);
}

int	ft_isdouble(char *s)
{
	if (*s == '+' || *s == '-')
		s++;
	while (ft_isdigit(*s))
		s++;
	if (*s == '\0' || ft_isspace(*s) || *s == ',')
		return (1);
	if (*s == '.')
	{
		s++;
		while (ft_isdigit(*s++))
		{
			if (*s == '\0' || ft_isspace(*s) || *s == ',')
				return (1);
		}
	}
	return (0);
}

void	skip_spaces(char **str)
{
	while (ft_isspace(**str))
		(*str)++;
}

bool	valid_eol(char **str)
{
	skip_spaces(str);
	if (**str == '\0' || **str == '\n')
		return (true);
	return (false);
}
