/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:51:50 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 17:19:55 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H

# include <math.h>
# define T_MIN (double)0.001
# define T_MAX INFINITY

# include "scene.h"
# include "ray.h"
# include "vector.h"

typedef struct s_quadratic
{
	double	a;
	double	half_b;
	double	c;
	double	dot_oc_cyorient;
	double	t;
	double	m;
}				t_quadratic;

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		t;
	bool		front_face;
	t_color		color;
}				t_hit_record;

bool	world_hit(const t_ray r, t_hit_record *rec, const t_hittable objects);
void	set_face_normal(const t_ray r,
			t_vec3 *outward_normal, bool *front_face);

bool	world_hit_sphere(const t_ray r, const t_hittable objects,
			t_hit_record *rec, double *closest_so_far);
bool	world_hit_plane(const t_ray r, const t_hittable objects,
			t_hit_record *rec, double *closest_so_far);
bool	world_hit_cylinder(const t_ray r, const t_hittable objects,
			t_hit_record *rec, double *closest_so_far);

typedef bool					(*t_world_hittable)(const t_ray r,
			const t_hittable objects, t_hit_record *rec,
			double *closest_so_far);

static const t_world_hittable	g_world_hittable[] = {
	world_hit_sphere,
	world_hit_plane,
	world_hit_cylinder
};

bool	world_hit_sphere(const t_ray r, const t_hittable objects,
							t_hit_record *rec, double *closest_so_far);
bool	world_hit_plane(const t_ray r, const t_hittable objects,
							t_hit_record *rec, double *closest_so_far);
bool	world_hit_cylinder(const t_ray r, const t_hittable objects,
							t_hit_record *rec, double *closest_so_far);

typedef bool	(*t_world_hittable)(const t_ray r, const t_hittable objects,
							t_hit_record *rec, double *closest_so_far);

static const t_world_hittable	g_world_hittable[] = {
	world_hit_sphere,
	world_hit_plane,
	world_hit_cylinder
};

bool	hit_sphere_record(const t_ray r, const t_sphere sp, double t_max,
							t_hit_record *temp_rec);

bool	hit_plane_record(const t_ray r, const t_plane pl, double t_max,
							t_hit_record *temp_rec);
bool	hit_plane(const t_ray r, const t_plane pl, double t_max, double *t);

bool	hit_cylinder_record(const t_ray r, const t_cylinder cy, double t_max,
							t_hit_record *temp_rec);
bool	hit_cylinder_plane_record(const t_ray r, const t_cylinder cy,
							const double t_max, t_hit_record *temp_rec);

#endif
