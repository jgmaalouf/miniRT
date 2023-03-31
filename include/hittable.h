/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:51:50 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 01:19:19 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H

# include <math.h>
# define T_MIN (double)0.001
# define T_MAX INFINITY

# include "scene.h"
# include "vector.h"
# include "ray.h"

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		t;
	bool		front_face;
	t_color		color;
}				t_hit_record;

bool	world_hit(const t_ray r, t_hit_record *rec, const t_hittable objects);
void	set_face_normal(const t_ray r, t_vec3 *outward_normal, bool *front_face);

bool	hit_sphere(const t_ray r, double t_max, const t_sphere sp, double *root);
bool	hit_sphere_record(const t_ray r, double t_max, const t_sphere sp,
							t_hit_record *temp_rec);
bool	hit_plane(const t_ray r, double t_max, const t_plane pl, double *t);
bool	hit_plane_record(const t_ray r, double t_max, const t_plane pl,
							t_hit_record *temp_rec);
bool	hit_cylinder_record(const t_ray r, double t_max, const t_cylinder cy,
							t_hit_record *temp_rec);
bool	hit_cylinder_plane_record_1(const t_ray r, const double t_max,
							const t_cylinder cy, t_hit_record *temp_rec);
bool	hit_cylinder_plane_record_2(const t_ray r, const double t_max,
							const t_cylinder cy, t_hit_record *temp_rec);

#endif
