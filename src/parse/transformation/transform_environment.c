/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_environment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:15:39 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/28 21:12:15 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "matrix.h"

void	get_rotation(t_vec3 camera_orient, double *rad_x, double *rad_y)
{
	
}

double	**get_camera_to_world_matrix(t_camera camera)
{
	double	**c_to_w;
	double	**temp;
	double	rad_x;
	double	rad_y;

	c_to_w = init_translation_m(camera.pos);
	get_rotation(camera.orient, &rad_x, &rad_y);
	matrix_matrix_mult(c_to_w, init_y_rotation_m(rad_y), temp);
	matrix_matrix_mult(temp, init_x_rotation_m(rad_x), c_to_w);
	return (c_to_w);
}

double	**inverse_matrix(double	**c_to_w)
{

}

void	scene_elements_transform(t_scene *scene)
{
	double	**c_to_w;
	double	**w_to_c;

	c_to_w = get_camera_to_world_matrix(scene->camera);
	w_to_c = inverse_matrix(c_to_w);
	apply_world_to_camera_matrix();
}
