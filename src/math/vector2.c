/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:49:49 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/06 19:49:56 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	vec3_dot(const t_vec3 u, const t_vec3 v)
{
	return (u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2]);
}

t_vec3	vec3_cross(const t_vec3 u, const t_vec3 v)
{
	return (vec3_constr(
			u.e[1] * v.e[2] - u.e[2] * v.e[1],
			u.e[2] * v.e[0] - u.e[0] * v.e[2],
			u.e[0] * v.e[1] - u.e[1] * v.e[0]));
}

t_vec3	vec3_scale_mult(const t_vec3 v, const double scale)
{
	return (vec3_constr(
			v.e[0] * scale,
			v.e[1] * scale,
			v.e[2] * scale));
}

t_vec3	vec3_scale_div(const t_vec3 v, const double scale)
{
	return (vec3_scale_mult(v, 1 / scale));
}

double	vec3_length_squared(const t_vec3 v)
{
	return (vec3_dot(v, v));
}
