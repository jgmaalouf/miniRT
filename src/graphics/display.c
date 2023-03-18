/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:31 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/18 15:17:03 by jmaalouf         ###   ########.fr       */
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

void	display(t_scene *scene)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	// mlx_set_setting(MLX_FULLSCREEN, true);
	mlx = mlx_init(scene->image.width, scene->image.height, "miniRT", true);
	if (!mlx)
		panic_exit("mlx init failure");
	img = mlx_new_image(mlx, scene->image.width, scene->image.height);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		panic_exit("mlx image failure");
	scene_render(scene, img);
	mlx_key_hook(mlx, &key_hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
}
