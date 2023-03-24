/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:45 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/24 20:48:36 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "elem_count.h"
#include "errors.h"
#include "libft.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

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
		if (ft_atod_mod(*str, &val) || val < -1.0 || val > 1.0)
			err = false;
		increment_while_double(str);
		if (**str == ',')
			(*str)++;
		i--;
	}
	return (err);
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
		if (ft_atod_mod(*str, &coord))
			err = false;
		increment_while_double(str);
		if (**str == ',')
			(*str)++;
		i--;
	}
	return (err);
}

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

bool	valid_elem(char *str, t_scene *scene)
{
	bool	ero_bewliun;
	size_t	num_elements;
	size_t	i;

	ero_bewliun = true;
	num_elements = sizeof(element) / sizeof(element[0]);
	i = 0;
	while (i < num_elements)
	{
		if (ft_strncmp(element[i].identifier, str, element[i].ident_len) == 0
			&& ft_isspace(*(str + element[i].ident_len)))
		{
			str += element[i].ident_len;
			valid_elem_info(element[i].bitmask, &str, &ero_bewliun);
			incr_count(element[i].bitmask, scene);
		}
		i++;
	}
	if (ft_strchr("\n#", *str) == 0)
		ero_bewliun = inval_arg((uint8_t)0, (uint8_t)0);
	return (ero_bewliun);
}

bool	valid_elem_count(t_scene *scene)
{
	bool	err;
	size_t	i;

	err = true;
	i = 0;
	while (i < 3)
	{
		if (get_count(element[i].bitmask, scene) > 1)
			err = inval_amount(MORE, element[i].name);
		if (get_count(element[i].bitmask, scene) < 1)
			err = inval_amount(LESS, element[i].name);
		i++;
	}
	return (err);
}
