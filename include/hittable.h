/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:51:50 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/12 00:08:27 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H

# include <float.h>
# define T_MIN (double)0
# define T_MAX DBL_MAX

# include "scene.h"
# include "vector.h"
# include "ray.h"

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		t;
	bool		front_face;
}				t_hit_record;

bool	world_hit(const t_ray r, t_hit_record *rec, t_hittable objects);

#endif
