/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:05 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/29 18:58:04 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "scene.h"
# include "ray.h"
# include "intersection.h"

void		display(t_scene *scene);
uint32_t	pixel_color(t_scene *scene, int x, int y);
double		shadow_hit(t_ray shadow_ray, t_hittable objects,
				t_hit_record hitpoint, t_vec3 light);
t_color		get_light_shade(const t_scene *scene, const t_hit_record hitpoint);

#endif
