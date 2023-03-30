/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:45 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/31 00:57:52 by jmaalouf         ###   ########.fr       */
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
	bool	valid;
	double	value;

	valid = true;
	value = 0;
	if (ft_atod_mod(*str, &value))
		valid = false;
	if (min != max)
		if (value < min || value > max)
			valid = false;
	increment_while_double(str);
	return (valid);
}

/* Checks the string for three valid values seperated by commas and increments
the string to the position after said values.
Valid value meaning a double, terminated by either a whitespace, ',' or '\0',
no less than min and no greater than max.
Returns true if valid values are found.

if min != max
min: lower limit to valid value
max: upper limit to valid value */
bool	validate_triple_val(char **str, const double min, const double max)
{
	bool	valid;
	double	value;
	int		i;

	valid = true;
	value = 0;
	i = 3;
	while (i > 0)
	{
		if (ft_atod_mod(*str, &value))
			valid = false;
		if (min != max)
			if (value < min || value > max)
				valid = false;
		increment_while_double(str);
		if (**str == ',')
			(*str)++;
		i--;
	}
	return (valid);
}

/* Loops through all tokens an element could possibly be defined by.
If the token defines said element, the proper function is called to validate
expected values in place of the token and increment the string accordingly.
Preceeding whitespaces are skipped.
Returns a bitmask defining what part of the string's content is invalid in
terms of the expected token */
uint8_t	validate_element_info(char **str, uint8_t element_bitmask)
{
	uint8_t	error;
	size_t	num_token;
	size_t	i;

	error = 0;
	num_token = sizeof(p) / sizeof(p[0]);
	i = 0;
	while (i < num_token)
	{
		skip_spaces(str);
		if (element_bitmask & p[i].token
			&& !p[i].validater(str, p[i].min, p[i].max))
		{
			error += p[i].token;
		}
		i++;
	}
	return (error);
}

/* Loops through all defined elements to check if the beginning of the string
matches the type identifier of an existing element.
If a there's match followed by a whitespace the string is incremented
accordingly, a function is called to check the expected following information
and another function to keep count of the different elements.
If str ends with anything but a '\n', '#' or '\0', the str represents an
invalid element. */
bool	validate_element(char *str, t_scene *scene, size_t line)
{
	uint8_t	error;
	size_t	num_elements;
	size_t	i;

	error = 0;
	num_elements = sizeof(element) / sizeof(element[0]);
	i = 0;
	while (i < num_elements)
	{
		if (ft_strncmp(element[i].id_str, str, element[i].id_len) == 0
			&& ft_isspace(*(str + element[i].id_len)))
		{
			str += element[i].id_len;
			error = validate_element_info(&str, element[i].bitmask);
			if (error)
				invalid_element(error, element[i].name, line);
			incr_count(element[i].bitmask, scene);
		}
		i++;
	}
	skip_spaces(&str);
	if (ft_strchr("\n#", *str) == 0)
		return (invalid_element((uint8_t)0, NULL, line), true);
	return (error);
}

/* Verifies that there is only one element defining each camera, light
and ambient light */
bool	validate_element_count(t_scene *scene)
{
	bool	valid;
	size_t	i;

	valid = true;
	i = 0;
	while (i < 3)
	{
		if (i != 2 && get_count(element[i].bitmask, scene) > 1)
		{
			invalid_element_amount(MORE, element[i].name);
			valid = false;
		}
		if (get_count(element[i].bitmask, scene) < 1)
		{
			invalid_element_amount(LESS, element[i].name);
			valid = false;
		}
		i++;
	}
	return (valid);
}
