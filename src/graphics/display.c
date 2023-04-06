/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:31 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/04/06 11:38:49 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "errors.h"
#include "scene.h"
#include "graphics.h"

#include <stdio.h>

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_worker	*workers;
	size_t		i;

	workers = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		i = 0;
		while (i < THREADS)
			pthread_cancel(workers[i++].thread);
		mlx_close_window(workers->scene->image.mlx);
	}
}

void	*render_routine(void *param)
{
	t_worker	*worker;
	int			x;
	int			y;

	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	worker = param;
	y = worker->id;
	while (y < worker->scene->image.height)
	{
		x = 0;
		while (x < worker->scene->image.width)
		{
			mlx_put_pixel(worker->scene->image.img, x, y, pixel_color(worker->scene, x, y));
			x++;
			pthread_testcancel();
		}
		y += THREADS;
	}
	return (NULL);
}

void	scene_render(t_worker *workers)
{
	size_t	i;

	i = 0;
	while (i < THREADS)
	{
		if (pthread_create(&workers[i].thread, NULL, &render_routine, &workers[i]) != 0)
			panic_exit("bad thread");
		i++;
	}
}

void	resize_scene(int32_t width, int32_t height, void *param)
{
	t_scene		*scene;
	t_worker	*workers;

	workers = param;
	scene = workers->scene;
	cancel_threads(workers);
	join_threads(workers);
	mlx_resize_image(scene->image.img, width, height);
	scene->image.height = height;
	scene->image.width = width;
	scene->image.ratio = scene->image.width / scene->image.height;
	scene_render(workers);
}

void	display(t_scene *scene)
{
	t_worker *workers;

	scene->image.mlx = mlx_init(scene->image.width, scene->image.height, "miniRT", true);
	if (!scene->image.mlx)
		panic_exit("mlx init failure");
	scene->image.img = mlx_new_image(scene->image.mlx,
			scene->image.width, scene->image.height);
	if (!scene->image.img
		|| (mlx_image_to_window(scene->image.mlx, scene->image.img, 0, 0) < 0))
		panic_exit("mlx image failure");
	workers = create_workers(scene);
	scene_render(workers);
	mlx_resize_hook(scene->image.mlx, &resize_scene, workers);
	mlx_key_hook(scene->image.mlx, &key_hook, workers);
	mlx_loop(scene->image.mlx);
	join_threads(workers);
	mlx_delete_image(scene->image.mlx, scene->image.img);
	mlx_terminate(scene->image.mlx);
	free(workers);
}
