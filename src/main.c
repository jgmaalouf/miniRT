/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:41:08 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/07 14:08:49 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cleanup(t_scene scene)
{
	free(scene.spheres);
	free(scene.planes);
	free(scene.cylinders);
}

int	main(int argc, char *argv[])
{
	t_scene	scene;

	if (argc != 2)
		return (inval_input(INVALID_ARGS));
	scene = parse(argv[1]);
	if (scene.error == true)
		return (EXIT_FAILURE);
	display(scene);
	cleanup(scene);
	return (EXIT_SUCCESS);
}
