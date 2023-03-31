/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:00:27 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/31 20:31:38 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "debug.h"

#include <stdio.h>

void	print_vec3(char *name, t_vec3 vec)
{
	printf("vector [%s]:\t[%f][%f][%f]\n", name, vec.e[0], vec.e[1], vec.e[2]);
}

void	print_scene(t_scene scene)
{
	print_amb_and_cam_and_light(scene);
	print_sphere(scene);
	print_plane(scene);
	print_cylinder(scene);
	print_cone(scene);
}
