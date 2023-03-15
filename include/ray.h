/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:32:04 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/15 09:27:10 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "scene.h"

# include <stdlib.h> // uint_t
# include "scene.h"

typedef struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
}				t_ray;

uint32_t	pixel_color(t_scene *scene, int x, int y);

t_ray		ray_constr(const t_point3 origin, const t_vec3 direction);
t_point3	ray_at(const t_ray ray, const double t);

#endif
