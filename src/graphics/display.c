/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:31 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/29 15:56:05 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "errors.h"
#include "scene.h"
#include "ray.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
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
	}
}

void resize_scene(int32_t width, int32_t height, void *param)
{
	t_scene *scene = (t_scene *)param;
	mlx_resize_image(scene->image.img, width, height);
	scene->image.height = height;
	scene->image.width = width;
	scene->image.ratio = scene->image.width / scene->image.height;
	scene_render(scene, scene->image.img);
}

void	display(t_scene *scene)
{
	mlx_t		*mlx;

	mlx = mlx_init(scene->image.width, scene->image.height, "miniRT", true);
	if (!mlx)
		panic_exit("mlx init failure");
	scene->image.img = mlx_new_image(mlx, scene->image.width, scene->image.height);
	if (!scene->image.img || (mlx_image_to_window(mlx, scene->image.img, 0, 0) < 0))
		panic_exit("mlx image failure");
	scene_render(scene, scene->image.img);
	mlx_resize_hook(mlx, &resize_scene, scene);
	mlx_key_hook(mlx, &key_hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, scene->image.img);
	mlx_terminate(mlx);
}
