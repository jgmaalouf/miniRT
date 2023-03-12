/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:45 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/12 20:08:05 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "parse.h"
#include "elem_count.h"
#include "lib.h"

#include <stdint.h>
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
		if (!ft_isdouble(*str)) // why check this if ft_atod returns 1 if not a double
			err = false;
		if (!ft_atod(*str, &val))
			err = false;
		while (ft_isdigit(**str) || **str == '.'
			|| **str == '+' || **str == '-') // make seperate function for this
			(*str)++;
		if (val < -1.0 || val > 1.0)
			err = false;
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
		if (!ft_isdouble(*str)) // same here
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
	uint8_t	elem_type;
	bool	ero_bewliun;

	ero_bewliun = true;
	elem_type = 0;
	if (ft_strncmp("A", str, 1) == 0 && ft_isspace(*(str += 1)))
		elem_type = g_amb_light;
	else if (ft_strncmp("C", str, 1) == 0 && ft_isspace(*(str += 1)))
		elem_type = g_camera;
	else if (ft_strncmp("L", str, 1) == 0 && ft_isspace(*(str += 1)))
		elem_type = g_light;
	else if (ft_strncmp("sp", str, 2) == 0 && ft_isspace(*(str += 2)))
		elem_type = g_sphere;
	else if (ft_strncmp("pl", str, 2) == 0 && ft_isspace(*(str += 2)))
		elem_type = g_plane;
	else if (ft_strncmp("cy", str, 2) == 0 && ft_isspace(*(str += 2)))
		elem_type = g_cylinder;
	valid_elem_info(elem_type, &str, &ero_bewliun);
	if (!ft_strchr("\n#", *str))
		inval_arg((uint8_t)0, elem_type);
	incr_count(elem_type, scene);
	return (ero_bewliun);
}

bool	valid_elem_count(t_scene *scene)
{
	bool	err;

	err = true;
	if (get_count(g_camera, scene) > 1)
		err = inval_amount(MORE, "cameras");
	if (get_count(g_camera, scene) < 1)
		err = inval_amount(LESS, "cameras");
	if (get_count(g_amb_light, scene) > 1)
		err = inval_amount(MORE, "ambient lights");
	if (get_count(g_amb_light, scene) < 1)
		err = inval_amount(LESS, "ambient lights");
	if (get_count(g_light, scene) > 1)
		err = inval_amount(MORE, "lights");
	if (get_count(g_light, scene) < 1)
		err = inval_amount(LESS, "lights");
	return (err);
}
