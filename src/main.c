#include "minirt.h"

void	cleanup(t_scene scene)
{
	free(scene.spheres);
	free(scene.planes);
	free(scene.cylinders);
}

void	print_scene(t_scene scene)
{
	printf("A\t%.1f\t\t\t\t\t\t%.1f,%.1f,%.1f\n\n", scene.amb_light.ratio, scene.amb_light.rgb.e[0], scene.amb_light.rgb.e[1], scene.amb_light.rgb.e[2]);
	printf("C\t%.1f,%.1f,%.1f\t%.1f,%.1f,%.1f\t%d\n\n", scene.camera.pos.e[0], scene.camera.pos.e[1], scene.camera.pos.e[2], scene.camera.orient.e[0], scene.camera.orient.e[1], scene.camera.orient.e[2], scene.camera.fov);
	printf("L\t%.1f,%.1f,%.1f\t\t\t%.1f\t\t%.1f,%.1f,%.1f\n\n", scene.light.pos.e[0], scene.light.pos.e[1], scene.light.pos.e[2], scene.light.ratio, scene.light.rgb.e[0], scene.light.rgb.e[1], scene.light.rgb.e[2]);
	printf("pl\t%.1f,%.1f,%.1f\t%.1f,%.1f,%.1f\t\t\t%.1f,%.1f,%.1f\n\n", scene.planes[0].pos.e[0], scene.planes[0].pos.e[1], scene.planes[0].pos.e[2], scene.planes[0].orient.e[0], scene.planes[0].orient.e[1], scene.planes[0].orient.e[2], scene.planes[0].rgb.e[0], scene.planes[0].rgb.e[1], scene.planes[0].rgb.e[2]);
	printf("sp\t%.1f,%.1f,%.1f\t\t\t%.1f\t\t%.1f,%.1f,%.1f\n\n", scene.spheres[0].pos.e[0], scene.spheres[0].pos.e[1], scene.spheres[0].pos.e[2], scene.spheres[0].diameter, scene.spheres[0].rgb.e[0], scene.spheres[0].rgb.e[1], scene.spheres[0].rgb.e[2]);
	printf("cy\t%.1f,%.1f,%.1f\t%.1f,%.1f,%.1f\t%.1f\t%.1f\t%.1f,%.1f,%.1f\n\n", scene.cylinders[0].pos.e[0], scene.cylinders[0].pos.e[1], scene.cylinders[0].pos.e[2], scene.cylinders[0].orient.e[0], scene.cylinders[0].orient.e[1], scene.cylinders[0].orient.e[2], scene.cylinders[0].diameter, scene.cylinders[0].height, scene.cylinders[0].rgb.e[0], scene.cylinders[0].rgb.e[1], scene.cylinders[0].rgb.e[2]);
}

int main(int argc, char *argv[])
{
	t_scene	scene;

	if (argc != 2)
		return (inval_input(INVALID_ARGS));
	scene = parse_scene(argv[1]);
	if (scene.error == true)
		return (EXIT_FAILURE);
	print_scene(scene);
	// display(scene);
	cleanup(scene);
	return (EXIT_SUCCESS);
}
