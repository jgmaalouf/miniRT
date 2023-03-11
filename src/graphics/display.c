/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:31 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/11 21:14:51 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "errors.h"
#include "graphics.h"
#include "color.h"
#include "scene.h"
#include "ray.h"

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

t_ray	get_next_ray(int x, int y, t_image img, t_camera cam)
{
	t_ray	ray;
	double	u;
	double	v;

	u = (double)x / (img.width - 1);
	v = (double)y / (img.height - 1);
	// printf("x:\t%i,\ty:\t%i\n", x, y);
	ray = ray_constr(
			cam.pos,
			vec3_substr(
				vec3_add(
					img.lower_left_corner,
					vec3_add(
						vec3_scale_mult(img.hori, u),
						vec3_scale_mult(img.vert, v)
						)
					),
				cam.pos
				)
			);
	return (ray);
}

double	hit_sphere(t_sphere sp, const t_ray ray)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_substr(ray.orig, sp.pos);
	a = vec3_dot(ray.dir, ray.dir);
	b = 2.0 * vec3_dot(oc, ray.dir);
	c = vec3_dot(oc, oc) - sp.diameter / 2 * sp.diameter / 2;
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (0.0);
	else
		return (1.0);
		// return ((-b - sqrt(discriminant)) / (2.0 * a));
}

t_color	ray_color(const t_ray r, t_scene *scene)
{
	t_vec3	unit_direction;
	double	t;
	t_color	white;
	t_color	blue;

	white = vec3_constr(1.0, 1.0, 1.0);
	blue = vec3_constr(0.5, 0.7, 1.0);
	t = hit_sphere(scene->hittable.spheres[0], r);
	if (t)
		return (vec3_constr(1, 0, 0));
	// if (t > 0.0)
	// {
	// 	t_vec3	n = vec3_unit(vec3_substr(ray_at(r, t), vec3_constr(0, 0, -1)));
	// 	return (
	// 		vec3_scale_mult(
	// 			vec3_constr(n.e[0] + 1, n.e[1] + 1, n.e[2] + 1),
	// 			0.5));
	// }
	unit_direction = vec3_unit(r.dir);
	t = 0.5 * (unit_direction.e[1] + 1.0);
	return (
		vec3_add(
			vec3_scale_mult(white, 1.0 - t),
			vec3_scale_mult(blue, t)
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
			r = get_next_ray(x, y, scene->image, scene->camera);
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
