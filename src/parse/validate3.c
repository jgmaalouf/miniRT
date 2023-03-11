/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:50 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/11 11:34:20 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool	valid_coord(char **str)
{
	int		i;
	double	coord;

	i = 3;
	while (i > 0)
	{
		if (!ft_isdouble(*str))
			return (false);
		if (!ft_atod(*str, &coord))
			return (false);
		while (ft_isdigit(**str) || **str == '.'
			|| **str == '+' || **str == '-')
			(*str)++;
		if (**str == ',')
			(*str)++;
		i--;
	}
	return (true);
}

bool	valid_orient(char **str)
{
	int		i;
	double	val;

	i = 3;
	while (i > 0)
	{
		if (!ft_isdouble(*str))
			return (false);
		if (!ft_atod(*str, &val))
			return (false);
		while (ft_isdigit(**str) || **str == '.'
			|| **str == '+' || **str == '-')
			(*str)++;
		if (val < -1.0 || val > 1.0)
			return (false);
		if (**str == ',')
			(*str)++;
		i--;
	}
	return (true);
}

bool	valid_fov(char **str)
{
	int	fov;

	if (!ft_isnumber(*str))
		return (false);
	if (ft_atoi_mod(*str, &fov) == 1
		|| fov > 180 || fov < 0)
		return (false);
	while (ft_isdigit(**str))
		(*str)++;
	return (true);
}

bool	valid_dbl_size(char **str)
{
	double	diam;

	if (!ft_isdouble(*str))
		return (false);
	if (!ft_atod(*str, &diam))
		return (false);
	while (ft_isdigit(**str) || **str == '.'
		|| **str == '+' || **str == '-')
		(*str)++;
	if (diam < 0.0)
		return (false);
	return (true);
}

bool	valid_rgb(char **str)
{
	int		i;
	int		val;

	i = 3;
	while (i > 0)
	{
		if (!ft_isnumber(*str))
			return (false);
		if (ft_atoi_mod(*str, &val) == 1 || val > 255 || val < 0)
			return (false);
		while (ft_isdigit(**str)
			|| **str == '+' || **str == '-')
			(*str)++;
		if (**str == ',')
			(*str)++;
		i--;
	}
	return (true);
}
