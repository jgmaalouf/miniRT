/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:31 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/21 14:27:04 by jmaalouf         ###   ########.fr       */
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

void	scene_render(t_scene *scene, mlx_image_t *mlx_img)
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

// void print_window(int32_t width, int32_t height, void *param)
// {
// 	t_scene *scene = (t_scene *)param;
// 	fflush(stdout);
// 	printf("%i\n", height);
// 	printf("%i\n", width);
// 	scene->image.height = height;
// 	scene->image.width = width;
// 	scene->image.ratio = scene->image.width / scene->image.height;
// 	scene->image.focal_len = 1.0;
// 	scene->image.viewport_width = 4.0;
// 	scene->image.viewport_height = scene->image.viewport_width / scene->image.ratio;
// 	scene->image.hori = vec3_constr(scene->image.viewport_width, 0, 0);
// 	scene->image.vert = vec3_constr(0, scene->image.viewport_height, 0);
// 	scene->image.lower_left_corner
// 		= vec3_subtr(
// 			scene->camera.pos,
// 			vec3_add(
// 				vec3_scale_div(scene->image.hori, 2),
// 				vec3_add(
// 					vec3_scale_div(scene->image.vert, 2),
// 					vec3_constr(0, 0, scene->image.focal_len)
// 					)
// 				)
// 			);
// 	mlx_resize_image(scene->image.img, width, height);
// }

void	display(t_scene *scene)
{
	mlx_t		*mlx;

	// mlx_set_setting(MLX_FULLSCREEN, true);
	mlx = mlx_init(scene->image.width, scene->image.height, "miniRT", true);
	if (!mlx)
		panic_exit("mlx init failure");
	scene->image.img = mlx_new_image(mlx, scene->image.width, scene->image.height);
	if (!scene->image.img || (mlx_image_to_window(mlx, scene->image.img, 0, 0) < 0))
		panic_exit("mlx image failure");
	scene_render(scene, scene->image.img);
	// mlx_resize_hook(mlx, &print_window, &scene);
	mlx_key_hook(mlx, &key_hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, scene->image.img);
	mlx_terminate(mlx);
}
