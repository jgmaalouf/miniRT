/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:32:05 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/30 20:30:11 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "matrix.h"

static void	set_p(t_vec3 *p, double new_p[4])
{
	p->e[0] = new_p[0];
	p->e[1] = new_p[1];
	p->e[2] = new_p[2];
}

static void	get_point(t_point3 *p, double op[4])
{
	op[0] = p->e[0];
	op[1] = p->e[1];
	op[2] = p->e[2];
	op[3] = 1.0;
}

void	transform_point(t_point3 *vec, double w_to_c[4][4])
{
	double	old_p[4];
	double	new_p[4];

	get_point(vec, old_p);
	matrix_vector_mult(w_to_c, old_p, new_p);
	set_p(vec, new_p);
}

static void	get_vector(t_vec3 *p, double op[4])
{
	op[0] = p->e[0];
	op[1] = p->e[1];
	op[2] = p->e[2];
	op[3] = 0.0;
}

void	transform_vector(t_vec3 *vec, double w_to_c[4][4])
{
	double	old_p[4];
	double	new_p[4];

	get_vector(vec, old_p);
	matrix_vector_mult(w_to_c, old_p, new_p);
	set_p(vec, new_p);
}
