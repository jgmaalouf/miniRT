/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:05 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/31 20:11:35 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "scene.h"
# include "ray.h"
# include "hittable.h"

void		display(t_scene *scene);
uint32_t	pixel_color(t_scene *scene, int x, int y);
double		shadow_hit(t_ray shadow_ray, t_hittable objects,
				t_hit_record hitpoint, t_vec3 light);
t_color		get_light_shade(const t_scene *scene, const t_hit_record hitpoint);

#endif
