/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:26:58 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 19:27:01 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "elem_count.h"
#include "debug.h"
#include "parse.h"
#include "scene.h"

void	print_scene(t_scene scene)
{
	printf("A\t%.1f\t\t\t\t\t\t\t\t%.1f,%.1f,%.1f\n\n", scene.amb_light.ratio, scene.amb_light.rgb.e[0], scene.amb_light.rgb.e[1], scene.amb_light.rgb.e[2]);
	printf("C\t%.1f,%.1f,%.1f\t\t%.1f,%.1f,%.1f\t%.1f\n\n", scene.camera.pos.e[0], scene.camera.pos.e[1], scene.camera.pos.e[2], scene.camera.orient.e[0], scene.camera.orient.e[1], scene.camera.orient.e[2], scene.camera.fov);
	for (size_t i = 0; i < get_count(g_light, &scene); i++)
		printf("L\t%.1f,%.1f,%.1f\t\t\t\t%.1f\t\t\t%.1f,%.1f,%.1f\n\n", scene.light[i].pos.e[0], scene.light[i].pos.e[1], scene.light[i].pos.e[2], scene.light[i].ratio, scene.light[i].rgb.e[0], scene.light[i].rgb.e[1], scene.light[i].rgb.e[2]);
	for (size_t i = 0; i < get_count(g_plane, &scene); i++)
		printf("pl\t%.1f,%.1f,%.1f\t\t%.1f,%.1f,%.1f\t\t\t\t%.1f,%.1f,%.1f\n\n", scene.hittable.planes[i].pos.e[0], scene.hittable.planes[i].pos.e[1], scene.hittable.planes[i].pos.e[2], scene.hittable.planes[i].orient.e[0], scene.hittable.planes[i].orient.e[1], scene.hittable.planes[i].orient.e[2], scene.hittable.planes[i].rgb.e[0], scene.hittable.planes[i].rgb.e[1], scene.hittable.planes[i].rgb.e[2]);
	for (size_t i = 0; i < get_count(g_sphere, &scene); i++)
		printf("sp\t%.1f,%.1f,%.1f\t\t\t\t%.1f\t\t\t%.1f,%.1f,%.1f\n\n", scene.hittable.spheres[i].pos.e[0], scene.hittable.spheres[i].pos.e[1], scene.hittable.spheres[i].pos.e[2], scene.hittable.spheres[i].diameter, scene.hittable.spheres[i].rgb.e[0], scene.hittable.spheres[i].rgb.e[1], scene.hittable.spheres[i].rgb.e[2]);
	for (size_t i = 0; i < get_count(g_cylinder, &scene); i++)
		printf("cy\t%.1f,%.1f,%.1f\t\t%.1f,%.1f,%.1f\t%.1f\t%.1f\t\t%.1f,%.1f,%.1f\n\n", scene.hittable.cylinders[i].pos.e[0], scene.hittable.cylinders[i].pos.e[1], scene.hittable.cylinders[i].pos.e[2], scene.hittable.cylinders[i].orient.e[0], scene.hittable.cylinders[i].orient.e[1], scene.hittable.cylinders[i].orient.e[2], scene.hittable.cylinders[i].diameter, scene.hittable.cylinders[i].height, scene.hittable.cylinders[i].rgb.e[0], scene.hittable.cylinders[i].rgb.e[1], scene.hittable.cylinders[i].rgb.e[2]);
	for (size_t i = 0; i < get_count(g_cone, &scene); i++)
		printf("co\t%.1f,%.1f,%.1f\t\t%.1f,%.1f,%.1f\t%.1f\t%.1f\t%.1f\t%.1f,%.1f,%.1f\n\n", scene.hittable.cones[i].pos.e[0], scene.hittable.cones[i].pos.e[1], scene.hittable.cones[i].pos.e[2], scene.hittable.cones[i].orient.e[0], scene.hittable.cones[i].orient.e[1], scene.hittable.cones[i].orient.e[2], scene.hittable.cones[i].diameter, scene.hittable.cones[i].height, scene.hittable.cones[i].angle, scene.hittable.cones[i].rgb.e[0], scene.hittable.cones[i].rgb.e[1], scene.hittable.cones[i].rgb.e[2]);
}

void	print_vec3(char *name, t_vec3 vec)
{
	printf("vector [%s]:\t[%f][%f][%f]\n", name, vec.e[0], vec.e[1], vec.e[2]);
}
