/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:50 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/11 21:21:15 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "parse.h"

#include <stdbool.h>

bool	valid_rgb(char **str)
{
	int		i;
	int		val;
	bool	err;

	err = true;
	skip_spaces(str);
	i = 3;
	while (i > 0)
	{
		if (!ft_isnumber(*str))
			err = false;
		if (ft_atoi_mod(*str, &val) == 1 || val > 255 || val < 0)
			err = false;
		while (ft_isdigit(**str)
			|| **str == '+' || **str == '-')
			(*str)++;
		if (**str == ',')
			(*str)++;
		i--;
	}
	return (err);
}

bool	valid_ratio(char **str)
{
	double	ratio;
	bool	err;

	err = true;
	skip_spaces(str);
	if (!ft_isdouble(*str))
		err = false;
	if (!ft_atod(*str, &ratio))
		err = false;
	while (ft_isdigit(**str) || **str == '.')
		(*str)++;
	if (ratio < 0.0 && ratio > 1.0)
		err = false;
	return (err);
}

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
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	if (i > 10)
		return (0);
	if (s[i] == '\0' || ft_isspace(s[i]) || s[i] == ',')
		return (1);
	if (s[i] == '.')
	{
		i++;
		while (ft_isdigit(s[i++]))
		{
			if (s[i] == '\0' || ft_isspace(s[i]) || s[i] == ',')
				return (1);
			if (i > 10)
				return (0);
		}
	}
	return (0);
}

void	skip_spaces(char **str)
{
	while (ft_isspace(**str))
		(*str)++;
}
