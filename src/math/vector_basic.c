/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:34 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/06 19:49:43 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vec3_constr(const double e0, const double e1, const double e2)
{
	t_vec3	vec3;

	vec3.e[0] = e0;
	vec3.e[1] = e1;
	vec3.e[2] = e2;
	return (vec3);
}

t_vec3	vec3_add(const t_vec3 u, const t_vec3 v)
{
	return (vec3_constr(
			u.e[0] + v.e[0],
			u.e[1] + v.e[1],
			u.e[2] + v.e[2]));
}

t_vec3	vec3_substr(const t_vec3 u, const t_vec3 v)
{
	return (vec3_constr(
			u.e[0] - v.e[0],
			u.e[1] - v.e[1],
			u.e[2] - v.e[2]));
}

t_vec3	vec3_mult(const t_vec3 u, const t_vec3 v)
{
	return (vec3_constr(
			u.e[0] * v.e[0],
			u.e[1] * v.e[1],
			u.e[2] * v.e[2]));
}

t_vec3	vec3_div(const t_vec3 u, const t_vec3 v)
{
	return (vec3_constr(
			u.e[0] / v.e[0],
			u.e[1] / v.e[1],
			u.e[2] / v.e[2]));
}
