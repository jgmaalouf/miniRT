/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:41:08 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/26 08:27:25 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "graphics.h"
#include "errors.h"
#include "memory_alloc.h"
#include "debug.h"

#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_scene	scene;

	if (argc != 2)
	{
		invalid_input(INVALID_ARGS);
		return (EXIT_FAILURE);
	}
	scene = parse(argv[1]);
	if (scene.error == true)
		return (EXIT_FAILURE);
	print_scene(scene);
	display(&scene);
	free_scene_elements(&scene);
	return (EXIT_SUCCESS);
}
