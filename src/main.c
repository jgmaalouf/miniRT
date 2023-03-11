/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:41:08 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/11 19:43:44 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "scene.h"
#include "graphics.h"
#include "errors.h"
#include "debug.h"

void	cleanup(t_scene *scene)
{
	free(scene->hittable.spheres);
	free(scene->hittable.planes);
	free(scene->hittable.cylinders);
}

int	main(int argc, char *argv[])
{
	t_scene	scene;

	if (argc != 2)
		return (inval_input(INVALID_ARGS));
	scene = parse(argv[1]);
	if (scene.error == true)
		return (EXIT_FAILURE);
	print_scene(scene);
	display(&scene);
	cleanup(&scene);
	return (EXIT_SUCCESS);
}
