/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:45 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/25 20:43:44 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "elem_count.h"
#include "errors.h"
#include "libft.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/* Checks the string for a single valid value and increments the string to the
position after said value.
Valid value meaning a double, terminated by either a whitespace, ',' or '\0',
no less than min and no greater than max.
Returns true if valid value is found.

if min != max
min: lower limit to valid value
max: upper limit to valid value */
bool	validate_single_val(char **str, const double min, const double max)
{
	double	value;
	bool	err;

	value = 0;
	err = true;
	if (ft_atod_mod(*str, &value))
		err = false;
	if (min != max)
		if (value < min || value > max)
			err = false;
	increment_while_double(str);
	return (err);
}

/* Checks the string for three valid values seperated by commas and
increments the string to the position after said values.
Valid value meaning a double, terminated by either a whitespace, ',' or '\0',
no less than min and no greater than max.
Returns true if valid values are found.

if min != max
min: lower limit to valid value
max: upper limit to valid value */
bool	validate_triple_val(char **str, const double min, const double max)
{
	int		i;
	double	value;
	bool	err;

	value = 0;
	err = true;
	i = 3;
	while (i > 0)
	{
		if (ft_atod_mod(*str, &value))
			err = false;
		if (min != max)
			if (value < min || value > max)
				err = false;
		increment_while_double(str);
		if (**str == ',')
			(*str)++;
		i--;
	}
	return (err);
}

/* Loops through all tokens an element could possibly be defined by.
If the token defines said element, the proper function is called to validate
expected values in place of the token and increment the string accordingly.
Preceeding whitespaces are skipped.
If any of the string's content is invalid in terms of the expected token,
an error message is printed and bool error is set to false */
void	validate_element_info(char **str, struct s_element element, bool *error)
{
	size_t	num_token;
	size_t	i;

	num_token = sizeof(p) / sizeof(p[0]);
	i = 0;
	while (i < num_token)
	{
		skip_spaces(str);
		if (element.bitmask & p[i].token
			&& !p[i].validater(str, p[i].min, p[i].max))
		{
			*error = inval_arg(p[i].token, element.name);
		}
		i++;
	}
}

/* Loops through all defined elements to check if the beginning of the string
matches the type identifier of an existing element.
If a there's match followed by a whitespace the string is incremented
accordingly, a function is called to check the expected following information
and another function to keep count of the different elements.
If str ends with anything but a '\n', '#' or '\0', the str represents an
invalid element. */
bool	validate_element(char *str, t_scene *scene)
{
	bool	error;
	size_t	num_elements;
	size_t	i;

	error = true;
	num_elements = sizeof(element) / sizeof(element[0]);
	i = 0;
	while (i < num_elements)
	{
		if (ft_strncmp(element[i].id_str, str, element[i].id_len) == 0
			&& ft_isspace(*(str + element[i].id_len)))
		{
			str += element[i].id_len;
			validate_element_info(&str, element[i], &error);
			incr_count(element[i].bitmask, scene);
		}
		i++;
	}
	skip_spaces(&str);
	if (ft_strchr("\n#", *str) == 0)
		error = inval_arg((uint8_t)0, "\b");
	return (error);
}

/* Verifies that there is only one element defining each camera, light
and ambient light */
bool	validate_element_count(t_scene *scene)
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
