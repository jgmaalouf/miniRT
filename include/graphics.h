/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:05 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/04/06 11:42:12 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "scene.h"
# include "ray.h"
# include "hittable.h"

void		display(t_scene *scene);
uint32_t	pixel_color(t_scene *scene, int x, int y);
t_color		ray_color(const t_ray r, t_scene *scene, int depth);
double		shadow_hit(t_ray shadow_ray, t_hittable objects,
				t_hit_record hitpoint, t_vec3 light);
t_color		get_light_shade(const t_scene *scene, const t_hit_record hitpoint, size_t i);

t_worker	*create_workers(t_scene *scene);
void		join_threads(t_worker *workers);
void		cancel_threads(t_worker *workers);

#endif
