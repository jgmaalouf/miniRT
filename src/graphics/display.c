/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:31 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/30 21:45:37 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "errors.h"
#include "scene.h"
#include "ray.h"

#include <stdio.h> // printf

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

void	*render_routine(void *param)
{
	t_worker	*worker;
	size_t		x;
	size_t		y;
	
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	worker = param;
	y = worker->start;
	while (y <= worker->end)
	{
		x = 0;
		while (x < worker->scene.image.width)
		{
			mlx_put_pixel(worker->scene.image.img, x, y, pixel_color(&worker->scene, x, y));
			x++;
		}
		y++;
	}
	return (NULL);
}

void	launch_worker(size_t start, size_t end, t_scene scene, size_t id)
{
	scene.workers[id].start = start;
	scene.workers[id].end = end;
	scene.workers[id].scene = scene;

	if (pthread_create(&scene.workers[id].thread, NULL, &render_routine, &scene.workers[id]) != 0)
		panic_exit("bad thread");
}

void	scene_render(t_scene *scene)
{
	size_t	worker_id;
	size_t	start_line;
	size_t	end_line;
	size_t	lines_per_thread;
	bool	odd;

	worker_id = 0;
	start_line = 0;
	odd = false;
	if ((int)scene->image.height % THREADS)
		odd = true;
	lines_per_thread = (int)scene->image.height / THREADS + odd;
	while(start_line < scene->image.height)
	{
		end_line = start_line + lines_per_thread - 1;
		if (end_line >= scene->image.height)
			end_line = scene->image.height - 1;
		launch_worker(start_line, end_line, *scene, worker_id++);
		start_line += lines_per_thread;
	}
}

// void resize_scene(int32_t width, int32_t height, void *param)
// {
// 	// TODO: When resizing kill off the threads first and then relaunch them
// 	t_scene *scene = (t_scene *)param;
	
// 	mlx_resize_image(scene->image.img, width, height);
// 	scene->image.height = height;
// 	scene->image.width = width;
// 	scene->image.ratio = scene->image.width / scene->image.height;
// 	scene_render(scene);
// }

void	display(t_scene scene)
{
	mlx_t		*mlx;

	mlx = mlx_init(scene.image.width, scene.image.height, "miniRT", true);
	if (!mlx)
		panic_exit("mlx init failure");
	scene.image.img = mlx_new_image(mlx, scene.image.width, scene.image.height);
	if (!scene.image.img || (mlx_image_to_window(mlx, scene.image.img, 0, 0) < 0))
		panic_exit("mlx image failure");
	scene_render(&scene);
	// mlx_resize_hook(mlx, &resize_scene, scene);
	mlx_key_hook(mlx, &key_hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, scene.image.img);
	mlx_terminate(mlx);
	
	size_t i = 0;
	while(pthread_join(scene.workers[i].thread, NULL) == 0)
		i++;
}
