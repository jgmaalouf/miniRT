/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:15:39 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 00:55:55 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "scene.h"
#include "vector.h"
#include "matrix.h"
#include "transform.h"

#include <stdio.h>
#include <math.h>

static double	get_x_rotation(t_vec3 cam_orient)
{
	t_vec3	cam_default;
	double	dot_product;
	double	discriminant;
	double	cos_angle;

	cam_default = vec3_constr(0, 0, -1);
	dot_product = cam_default.e[1] * cam_orient.e[1] + cam_default.e[2] * cam_orient.e[2];
	discriminant = (cam_default.e[1] * cam_default.e[1]
			+ cam_default.e[2] * cam_default.e[2])
			* (cam_orient.e[1] * cam_orient.e[1]
			+ cam_orient.e[2] * cam_orient.e[2]);
	if (discriminant == 0.0)
		return (0);
	cos_angle = dot_product / sqrt(discriminant);
	if (cam_orient.e[1] < 0)
		return (-acos(cos_angle));
	return (acos(cos_angle));
}

static double	get_y_rotation(t_vec3 cam_orient)
{
	t_vec3	cam_default;
	double	cos_angle;
	double	discriminant;
	double	dot_product;

	cam_default = vec3_constr(0, 0, -1);
	dot_product = cam_default.e[0] * cam_orient.e[0] + cam_default.e[2] * cam_orient.e[2];
	discriminant = (cam_default.e[0] * cam_default.e[0]
			+ cam_default.e[2] * cam_default.e[2])
			* (cam_orient.e[0] * cam_orient.e[0]
			+ cam_orient.e[2] * cam_orient.e[2]);
	if (discriminant == 0.0)
		return (0);
	cos_angle = dot_product / sqrt(discriminant);
	if (cam_orient.e[0] <= 0)
		return (acos(cos_angle));
	return (-acos(cos_angle));
}

static void	get_world_to_camera_matrix(t_camera camera, double c_to_w[4][4])
{
	double	temp[4][4];
	double	x_rot_m[4][4];
	double	y_rot_m[4][4];

	init_translation_m(camera.pos, c_to_w);
	init_x_rotation_m(get_x_rotation(camera.orient), x_rot_m);
	matrix_matrix_mult(c_to_w, x_rot_m, temp);
	ft_memcpy(c_to_w, temp, 4 * 4 * sizeof(double));
	init_y_rotation_m(get_y_rotation(camera.orient), y_rot_m);
	matrix_matrix_mult(c_to_w, y_rot_m, temp);
	ft_memcpy(c_to_w, temp, 4 * 4 * sizeof(double));
}

static void	apply_world_to_camera_matrix(t_scene *scene, double w_to_c[4][4])
{
	size_t	num_hittable;
	size_t	i;

	num_hittable = sizeof(element) / sizeof(element[0]) - 2; 
	i = 0;
	while (i < num_hittable)
	{
		g_hittable_transform[i](scene, w_to_c);
		i++;
	}
}

void	transform(t_scene *scene)
{
	double	w_to_c[4][4];

	get_world_to_camera_matrix(scene->camera, w_to_c);
	apply_world_to_camera_matrix(scene, w_to_c);
}
