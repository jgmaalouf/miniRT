/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_environment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:15:39 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/27 19:31:18 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	get_world_to_camera_matrix(t_camera camera)
{
	get_camera_to_world_matrix();
	inverse();
}

void	scene_elements_transform(t_scene *scene)
{
	get_world_to_camera_matrix(scene->camera);
	apply_world_to_camera_matrix();
}
