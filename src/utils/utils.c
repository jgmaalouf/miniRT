/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:06:08 by amorvai           #+#    #+#             */
/*   Updated: 2023/04/02 17:39:29 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

#include <stdlib.h>

double	random_dbl(double min, double max)
{
	double	random;

	random = ((max - min) * arc4random_uniform(RAND_MAX)) / ((double)RAND_MAX + min);
	return (random);
}

void	skip_spaces(char **str)
{
	while (ft_isspace(**str))
		(*str)++;
}

void	increment_while_double(char **str)
{
	while (ft_isdigit(**str) || **str == '.' || **str == '+' || **str == '-')
		(*str)++;
}

void	fill_single_val(char **str, double *val)
{
	skip_spaces(str);
	ft_atod_mod(*str, val);
	increment_while_double(str);
}

void	fill_triple_val(char **str, t_vec3 *triple_val)
{
	fill_single_val(str, &triple_val->e[0]);
	(*str)++;
	fill_single_val(str, &triple_val->e[1]);
	(*str)++;
	fill_single_val(str, &triple_val->e[2]);
}
