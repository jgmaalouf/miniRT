#include <stdio.h>
#include "elem_count.h"
#include "debug.h"
#include "parse.h"
#include "scene.h"

void	print_scene(t_scene scene)
{
	printf("A\t%.1f\t\t\t\t\t\t\t%.1f,%.1f,%.1f\n\n", scene.amb_light.ratio, scene.amb_light.rgb.e[0], scene.amb_light.rgb.e[1], scene.amb_light.rgb.e[2]);
	printf("C\t%.1f,%.1f,%.1f\t\t%.1f,%.1f,%.1f\t%d\n\n", scene.camera.pos.e[0], scene.camera.pos.e[1], scene.camera.pos.e[2], scene.camera.orient.e[0], scene.camera.orient.e[1], scene.camera.orient.e[2], scene.camera.fov);
	printf("L\t%.1f,%.1f,%.1f\t\t\t\t%.1f\t\t%.1f,%.1f,%.1f\n\n", scene.light.pos.e[0], scene.light.pos.e[1], scene.light.pos.e[2], scene.light.ratio, scene.light.rgb.e[0], scene.light.rgb.e[1], scene.light.rgb.e[2]);
	for (int i = 0; i < get_count(g_plane, &scene); i++)
		printf("pl\t%.1f,%.1f,%.1f\t\t%.1f,%.1f,%.1f\t\t\t%.1f,%.1f,%.1f\n\n", scene.hittable.planes[i].pos.e[0], scene.hittable.planes[i].pos.e[1], scene.hittable.planes[i].pos.e[2], scene.hittable.planes[i].orient.e[0], scene.hittable.planes[i].orient.e[1], scene.hittable.planes[i].orient.e[2], scene.hittable.planes[i].rgb.e[0], scene.hittable.planes[i].rgb.e[1], scene.hittable.planes[i].rgb.e[2]);
	for (int i = 0; i < get_count(g_sphere, &scene); i++)
		printf("sp\t%.1f,%.1f,%.1f\t\t\t\t%.1f\t\t%.1f,%.1f,%.1f\n\n", scene.hittable.spheres[i].pos.e[0], scene.hittable.spheres[i].pos.e[1], scene.hittable.spheres[i].pos.e[2], scene.hittable.spheres[i].diameter, scene.hittable.spheres[i].rgb.e[0], scene.hittable.spheres[i].rgb.e[1], scene.hittable.spheres[i].rgb.e[2]);
	for (int i = 0; i < get_count(g_cylinder, &scene); i++)
		printf("cy\t%.1f,%.1f,%.1f\t\t%.1f,%.1f,%.1f\t%.1f\t%.1f\t%.1f,%.1f,%.1f\n\n", scene.hittable.cylinders[i].pos.e[0], scene.hittable.cylinders[i].pos.e[1], scene.hittable.cylinders[i].pos.e[2], scene.hittable.cylinders[i].orient.e[0], scene.hittable.cylinders[i].orient.e[1], scene.hittable.cylinders[i].orient.e[2], scene.hittable.cylinders[i].diameter, scene.hittable.cylinders[i].height, scene.hittable.cylinders[i].rgb.e[0], scene.hittable.cylinders[i].rgb.e[1], scene.hittable.cylinders[i].rgb.e[2]);
}

void	print_vec3(char *name, t_vec3 vec)
{
	printf("vector [%s]:\t[%f][%f][%f]\n", name, vec.e[0], vec.e[1], vec.e[2]);
}
