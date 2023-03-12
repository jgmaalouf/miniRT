/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:50 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/12 19:45:55 by amorvai          ###   ########.fr       */
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
		if (!ft_isnumber(*str)) // necessary?
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

bool	valid_dbl_size(char **str)
{
	double	diam;
	bool	err;

	err = true;
	skip_spaces(str);
	if (!ft_isdouble(*str)) // same here
		err = false;
	if (!ft_atod(*str, &diam))
		err = false;
	while (ft_isdigit(**str) || **str == '.'
		|| **str == '+' || **str == '-')
		(*str)++;
	if (diam < 0.0)
		err = false;
	return (err);
}

bool	valid_ratio(char **str)
{
	double	ratio;
	bool	err;

	err = true;
	skip_spaces(str);
	if (!ft_isdouble(*str)) // same here
		err = false;
	if (!ft_atod(*str, &ratio))
		err = false;
	while (ft_isdigit(**str) || **str == '.')
		(*str)++;
	if (ratio < 0.0 && ratio > 1.0) // should be or
		err = false;
	return (err);
}

bool	valid_fov(char **str)
{
	int	fov;
	bool	err;

	err = true;
	skip_spaces(str);
	if (!ft_isnumber(*str)) // necessary?
		err = false;
	if (ft_atoi_mod(*str, &fov) == 1
		|| fov > 180 || fov < 0) 
		err = false;
	while (ft_isdigit(**str)) // doesnt take plus or minus into account
		(*str)++;
	return (err);
}
