/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:32:04 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/29 18:26:28 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "scene.h"

typedef struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
}				t_ray;

t_ray		ray_constr(const t_point3 origin, const t_vec3 direction);
t_point3	ray_at(const t_ray ray, const double t);

#endif
