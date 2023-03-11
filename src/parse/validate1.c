/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:45 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/11 19:42:49 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include "errors.h"
#include "parse.h"
#include "lib.h"

void	valid_elem_info(uint8_t elem_type, char **str, bool *ero_bewliun)
{
	if (elem_type & TOK_COORD && !valid_coord(str))
		*ero_bewliun = inval_arg(TOK_COORD, elem_type);
	if (elem_type & TOK_ORIENT && !valid_orient(str))
		*ero_bewliun = inval_arg(TOK_ORIENT, elem_type);
	if (elem_type & TOK_FOV && !valid_fov(str))
		*ero_bewliun = inval_arg(TOK_FOV, elem_type);
	if (elem_type & TOK_RATIO && !valid_ratio(str))
		*ero_bewliun = inval_arg(TOK_RATIO, elem_type);
	if (elem_type & TOK_DIAMETER && !valid_dbl_size(str))
		*ero_bewliun = inval_arg(TOK_DIAMETER, elem_type);
	if (elem_type & TOK_HEIGHT && !valid_dbl_size(str))
		*ero_bewliun = inval_arg(TOK_HEIGHT, elem_type);
	if (elem_type & TOK_RGB && !valid_rgb(str))
		*ero_bewliun = inval_arg(TOK_RGB, elem_type);
	skip_spaces(str);
}

bool	valid_coord(char **str)
{
	int		i;
	double	coord;
	bool	err;

	err = true;
	skip_spaces(str);
	i = 3;
	while (i > 0)
	{
		if (!ft_isdouble(*str))
			err = false;
		if (!ft_atod(*str, &coord))
			err = false;
		while (ft_isdigit(**str) || **str == '.'
			|| **str == '+' || **str == '-')
			(*str)++;
		if (**str == ',')
			(*str)++;
		i--;
	}
	return (err);
}

bool	valid_orient(char **str)
{
	int		i;
	double	val;
	bool	err;

	err = true;
	skip_spaces(str);
	i = 3;
	while (i > 0)
	{
		if (!ft_isdouble(*str))
			err = false;
		if (!ft_atod(*str, &val))
			err = false;
		while (ft_isdigit(**str) || **str == '.'
			|| **str == '+' || **str == '-')
			(*str)++;
		if (val < -1.0 || val > 1.0)
			err = false;
		if (**str == ',')
			(*str)++;
		i--;
	}
	return (err);
}

bool	valid_fov(char **str)
{
	int	fov;
	bool	err;

	err = true;
	skip_spaces(str);
	if (!ft_isnumber(*str))
		err = false;
	if (ft_atoi_mod(*str, &fov) == 1
		|| fov > 180 || fov < 0)
		err = false;
	while (ft_isdigit(**str))
		(*str)++;
	return (err);
}

bool	valid_dbl_size(char **str)
{
	double	diam;
	bool	err;

	err = true;
	skip_spaces(str);
	if (!ft_isdouble(*str))
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
