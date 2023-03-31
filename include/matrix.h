/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:21:37 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 16:46:44 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

void	matrix_matrix_mult(double mtrx1[4][4],
			double mtrx2[4][4], double result_m[4][4]);
void	matrix_vector_mult(double matrix[4][4],
			double vector[4], double result_v[4]);

void	init_translation_m(t_vec3 camera_position, double c_to_w[4][4]);
void	init_x_rotation_m(double rad, double rotation_x_m[4][4]);
void	init_y_rotation_m(double rad, double rotation_y_m[4][4]);
// void	init_z_rotation_m(double rad, double rotation_z_m[4][4]);

#endif
