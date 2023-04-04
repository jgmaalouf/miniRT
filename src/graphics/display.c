/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:31 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/04/04 22:41:26 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "errors.h"
#include "scene.h"
#include "graphics.h"

#include <stdio.h>

void	key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

void	print_loading_screen(int line, int total)
{
	fflush(stdout);
	printf("Rendering: %i%%\r", (int)((line / (double)total) * 101.0));
}

t_worker	*create_workers(t_scene *scene)
{
	size_t		i;
	t_worker	*workers;

	workers = malloc(sizeof(t_worker) * THREADS);
	if (workers == NULL)
		panic_exit("bad alloc");
	i = 0;
	while (i < THREADS)
	{
		workers[i].id = i;
		workers[i].scene = scene;
		i++;
	}
	return (workers);
}

void	*scene_render(void *param)
{
	t_worker	*worker;
	int			x;
	int			y;

	worker = param;
	y = worker->id;
	while (y < worker->scene->image.height)
	{
		x = 0;
		while (x < worker->scene->image.width)
		{
			mlx_put_pixel(worker->scene->image.img, x, y, pixel_color(worker->scene, x, y));
			x++;
		}
		y += THREADS;
	}
	return (NULL);
}

t_worker	*scene_render_threads(t_scene *scene)
{
	size_t		i;
	t_worker	*workers;

	workers = create_workers(scene);
	i = 0;
	while (i < THREADS)
	{
		if (pthread_create(&workers[i].thread, NULL, &scene_render, &workers[i]) != 0)
			panic_exit("bad thread");
		i++;
	}
	return (workers);
}

/* void	scene_render(t_scene *scene, mlx_image_t *mlx_img)
{
	int			x;
	int			y;

	y = 0;
	while (y < scene->image.height)
	{
		x = 0;
		while (x < scene->image.width)
		{
			mlx_put_pixel(mlx_img, x, y, pixel_color(scene, x, y));
			x++;
		}
		y++;
		print_loading_screen(y, scene->image.height);
	}
}

void	resize_scene(int32_t width, int32_t height, void *param)
{
	t_scene	*scene;

	scene = param;
	mlx_resize_image(scene->image.img, width, height);
	scene->image.height = height;
	scene->image.width = width;
	scene->image.ratio = scene->image.width / scene->image.height;
	scene_render(scene, scene->image.img);
}
*/

void	display(t_scene *scene)
{
	mlx_t	*mlx;

	mlx = mlx_init(scene->image.width, scene->image.height, "miniRT", true);
	if (!mlx)
		panic_exit("mlx init failure");
	scene->image.img = mlx_new_image(mlx,
			scene->image.width, scene->image.height);
	if (!scene->image.img
		|| (mlx_image_to_window(mlx, scene->image.img, 0, 0) < 0))
		panic_exit("mlx image failure");
	t_worker *workers = scene_render_threads(scene);
	// scene_render(scene, scene->image.img);
	// mlx_resize_hook(mlx, &resize_scene, scene);
	mlx_key_hook(mlx, &key_hook, mlx);
	mlx_loop(mlx);
	size_t	i = 0;
	mlx_delete_image(mlx, scene->image.img);
	mlx_terminate(mlx);
	while (i < THREADS)
	{
		pthread_join(workers[i].thread, NULL);
		i++;
	}
	free(workers);
}

/* So what we can do is to render scenes using threads.
You send threads to do a specific thing
So depending on the number of threads I have */
