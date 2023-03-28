/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:21:37 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/28 20:26:23 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

double	**matrix_matrix_mult(double **mtrx1, double **mtrx2, double **result_m);
double	*matrix_vector_mult(double **matrix, double *vector, double *result_v);

double	**init_translation_m(t_vec3 camera_position);
double	**init_x_rotation_m(double rad);
double	**init_y_rotation_m(double rad);
double	**init_z_rotation_m(double rad);

#endif
