/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:07:28 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 00:37:32 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "scene.h"
# include "vector.h"

void	transform_light(t_scene *scene, double w_to_c[4][4]);
void	transform_hittable_sphere(t_scene *scene, double w_to_c[4][4]);
void	transform_hittable_plane(t_scene *scene, double w_to_c[4][4]);
void	transform_hittable_cylinder(t_scene *scene, double w_to_c[4][4]);

typedef void	(*t_transform)(t_scene *scene, double w_to_c[4][4]);

static const t_transform	g_hittable_transform[] = {
	transform_light,
	transform_hittable_sphere,
	transform_hittable_plane,
	transform_hittable_cylinder
};

void	transform_vector(t_vec3 *vec, double w_to_c[4][4]);
void	transform_point(t_point3 *vec, double w_to_c[4][4]);

#endif
