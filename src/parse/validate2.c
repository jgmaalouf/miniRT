/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:50 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/24 15:42:48 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"

#include <stdbool.h>

bool	valid_rgb(char **str)
{
	int		i;
	double	val;
	bool	err;

	err = true;
	skip_spaces(str);
	i = 3;
	while (i > 0)
	{
		if (ft_atod_mod(*str, &val) || val > 255.0 || val < 0.0)
			err = false;
		increment_while_double(str);
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
	if (ft_atod_mod(*str, &diam) || diam < 0.0)
		err = false;
	increment_while_double(str);
	return (err);
}

bool	valid_ratio(char **str)
{
	double	ratio;
	bool	err;

	err = true;
	skip_spaces(str);
	if (ft_atod_mod(*str, &ratio) || ratio < 0.0 || ratio > 1.0)
		err = false;
	increment_while_double(str);
	return (err);
}

bool	valid_fov(char **str)
{
	double	fov;
	bool	err;

	err = true;
	skip_spaces(str);
	if (ft_atod_mod(*str, &fov) || fov > 180.0 || fov < 0.0)
		err = false;
	increment_while_double(str);
	return (err);
}
