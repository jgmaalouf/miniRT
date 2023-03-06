/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:48 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/06 19:40:49 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool	valid_ratio(char **str)
{
	double	ratio;

	if (!ft_isdouble(*str))
		return (false);
	if (!ft_atod(*str, &ratio))
		return (false);
	while (ft_isdigit(**str) || **str == '.')
		(*str)++;
	if (ratio >= 0.0 && ratio <= 1.0)
		return (true);
	return (false);
}

bool	valid_amb_light(char *str)
{
	str++;
	skip_spaces(&str);
	if (!valid_ratio(&str))
		return (inval_arg(RATIO, "ambient light"));
	skip_spaces(&str);
	if (!valid_rgb(&str))
		return (inval_arg(RGB, "ambient light"));
	if (!valid_eol(&str))
		return (inval_arg(ELEM, "ambient light"));
	incr_count(amb_lights);
	return (true);
}
