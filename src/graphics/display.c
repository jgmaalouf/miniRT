/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:31 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/07 15:32:05 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void key_hook(mlx_key_data_t keydata, void* param)
{
	mlx_t *mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

void	scene_render(t_scene *scene, mlx_image_t *img)
{
	(void)(scene);
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (x % 2 == 0 && y % 2 == 0)
				mlx_put_pixel(img, x, y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
}

void	display(t_scene *scene)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	// mlx_set_setting(MLX_FULLSCREEN, true);
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		panic("mlx init failure");
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		panic("mlx image failure");
	scene_render(scene, img);
	mlx_key_hook(mlx, &key_hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
}
