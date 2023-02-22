#include "minirt.h"

int main(int argc, char *argv[])
{
	t_scene	scene;

	if (argc != 2)
		return (inval_input(INVALID_ARGS));
	scene = parse_scene(argv[1]);
	if (scene.error == true)
		return (EXIT_FAILURE);
	// display(scene);
	// cleanup(scene);
	return (EXIT_SUCCESS);
}
