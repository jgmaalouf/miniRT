/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:31 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/07 14:22:30 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void key_hook(mlx_key_data_t keydata, void* param)
{
	mlx_t *mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

void	display(t_scene scene)
{
	(void)(scene);
	mlx_t		*mlx;
	mlx_image_t	*img;
	double		aspect_ratio = 16.0 / 9.0;
	const int	image_width = 1920;
	const int	image_height = (int)(image_width / aspect_ratio);

	mlx = mlx_init(image_width, image_height, "Window", true);
	if (!mlx)
		panic("MLX failure");
	img = mlx_new_image(mlx, image_width, image_height);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_put_pixel(img, 20, 20, 0xFFFFFF);
	mlx_key_hook(mlx, &key_hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
}
