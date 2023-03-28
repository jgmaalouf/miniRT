/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:16 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/28 15:07:47 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct s_vec3
{
	double	e[3];
}				t_vec3;

typedef t_vec3	t_point3;
typedef t_vec3	t_color;

t_vec3	vec3_constr(const double e0, const double e1, const double e2);

t_vec3	vec3_add(const t_vec3 u, const t_vec3 v);
t_vec3	vec3_subtr(const t_vec3 u, const t_vec3 v);
t_vec3	vec3_mult(const t_vec3 u, const t_vec3 v);
t_vec3	vec3_div(const t_vec3 u, const t_vec3 v);

double	vec3_dot(const t_vec3 u, const t_vec3 v);
t_vec3	vec3_cross(const t_vec3 u, const t_vec3 v);

t_vec3	vec3_scale_mult(const t_vec3 v, const double scale);
t_vec3	vec3_scale_div(const t_vec3 v, const double scale);

t_vec3	vec3_unit(t_vec3 v);

double	vec3_length(const t_vec3 v);
double	vec3_length_squared(const t_vec3 v);

t_vec3	vec3_random(double min, double max);
t_vec3	vec3_random_unit(void);

t_vec3	vec3_clamp(t_vec3 vec, double min, double max);

#endif
