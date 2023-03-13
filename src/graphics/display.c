/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:31 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/13 15:31:46 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "errors.h"
#include "debug.h"
#include "color.h"
#include "scene.h"
#include "ray.h"
#include "hittable.h"

#include <stdio.h> // printf

void	key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

void		pixel_color(const t_ray r, t_scene *scene, t_color *color, int i)
{
	*color = vec3_add(*color, ray_color(r, scene));
	if (i == SPP - 1)
	{
		// printf("hi %i\n", i);
		*color = vec3_scale_div(*color, SPP);
	}
}

void	scene_render(t_scene *scene, mlx_image_t *mlx_img)
{
	int			x;
	int			y;
	t_ray		r;
	int			i;
	t_color		color;

	y = 0;
	while (y < scene->image.height)
	{
		// printf("%i\n", y);
		x = 0;
		while (x < scene->image.width)
		{
			i = 0;
			while (i < SPP || i == 0)
			{
				r = get_next_ray(scene->image.width - x, scene->image.height - y,
						scene->image, scene->camera);
				pixel_color(r, scene, &color, i);
				i++;
			}
			mlx_put_pixel(mlx_img, x, y, translate_colors(color.e[0], color.e[1], color.e[2]));
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
