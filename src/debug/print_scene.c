#include "minirt.h"

void	print_scene(t_scene scene)
{
	printf("A\t%.1f\t\t\t\t\t\t\t%.1f,%.1f,%.1f\n\n", scene.amb_light.ratio, scene.amb_light.rgb.e[0], scene.amb_light.rgb.e[1], scene.amb_light.rgb.e[2]);
	printf("C\t%.1f,%.1f,%.1f\t\t%.1f,%.1f,%.1f\t%d\n\n", scene.camera.pos.e[0], scene.camera.pos.e[1], scene.camera.pos.e[2], scene.camera.orient.e[0], scene.camera.orient.e[1], scene.camera.orient.e[2], scene.camera.fov);
	printf("L\t%.1f,%.1f,%.1f\t\t\t\t%.1f\t\t%.1f,%.1f,%.1f\n\n", scene.light.pos.e[0], scene.light.pos.e[1], scene.light.pos.e[2], scene.light.ratio, scene.light.rgb.e[0], scene.light.rgb.e[1], scene.light.rgb.e[2]);
	for (int i = 0; i < get_count(planes); i++)
		printf("pl\t%.1f,%.1f,%.1f\t\t%.1f,%.1f,%.1f\t\t\t%.1f,%.1f,%.1f\n\n", scene.planes[i].pos.e[0], scene.planes[i].pos.e[1], scene.planes[i].pos.e[2], scene.planes[i].orient.e[0], scene.planes[i].orient.e[1], scene.planes[i].orient.e[2], scene.planes[i].rgb.e[0], scene.planes[i].rgb.e[1], scene.planes[i].rgb.e[2]);
	for (int i = 0; i < get_count(spheres); i++)
		printf("sp\t%.1f,%.1f,%.1f\t\t\t\t%.1f\t\t%.1f,%.1f,%.1f\n\n", scene.spheres[i].pos.e[0], scene.spheres[i].pos.e[1], scene.spheres[i].pos.e[2], scene.spheres[i].diameter, scene.spheres[i].rgb.e[0], scene.spheres[i].rgb.e[1], scene.spheres[i].rgb.e[2]);
	for (int i = 0; i < get_count(cylinders); i++)
		printf("cy\t%.1f,%.1f,%.1f\t\t%.1f,%.1f,%.1f\t%.1f\t%.1f\t%.1f,%.1f,%.1f\n\n", scene.cylinders[i].pos.e[0], scene.cylinders[i].pos.e[1], scene.cylinders[i].pos.e[2], scene.cylinders[i].orient.e[0], scene.cylinders[i].orient.e[1], scene.cylinders[i].orient.e[2], scene.cylinders[i].diameter, scene.cylinders[i].height, scene.cylinders[i].rgb.e[0], scene.cylinders[i].rgb.e[1], scene.cylinders[i].rgb.e[2]);
}