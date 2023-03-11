/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:32:04 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/11 20:48:13 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"

typedef struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
}				t_ray;

t_ray		ray_constr(const t_point3 origin, const t_vec3 direction);

t_point3	ray_at(const t_ray ray, const double t);

#endif
