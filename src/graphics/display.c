/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:31 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/13 07:31:14 by amorvai          ###   ########.fr       */
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

void	calc_lower_left_corner(t_image *img, t_camera cam)
{
	img->viewport_height = 2.0;
	img->viewport_width = img->ratio * img->viewport_height;
	img->hori = vec3_constr(img->viewport_width, 0, 0);
	img->vert = vec3_constr(0, img->viewport_height, 0);
	// print_vec3("img->hori", img->hori);
	// print_vec3("img->vert", img->vert);
	// print_vec3("cam.pos", cam.pos);
	img->lower_left_corner
		= vec3_substr(
			cam.pos,
			vec3_add(
				vec3_scale_div(img->hori, 2),
				vec3_add(
					vec3_scale_div(img->vert, 2),
					vec3_constr(0, 0, img->focal_len)
					)
				)
			);
}

uint32_t	pixel_color(const t_ray r, t_scene *scene)
{
	t_color	color;

	color = ray_color(r, scene);
	return (translate_colors(color.e[0], color.e[1], color.e[2]));
}

void	scene_render(t_scene *scene, mlx_image_t *mlx_img)
{
	int		x;
	int		y;
	t_ray	r;

	calc_lower_left_corner(&scene->image, scene->camera);
	// print_vec3("lower_left_corner", scene->img.lower_left_corner);
	y = 0;
	while (y < scene->image.height)
	{
		x = 0;
		while (x < scene->image.width)
		{
			r = get_next_ray(scene->image.width - x, scene->image.height - y,
					scene->image, scene->camera);
			mlx_put_pixel(mlx_img, x, y, pixel_color(r, scene));
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
