/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:26:20 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 13:03:01 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

#include <math.h>

//
//	TRANSLATION	MATRIX
//	{	1	0	0	offset_x	}
//	{	0	1	0	offset_y	}
//	{	0	0	1		0		}
//	{	0	0	0		1		}
//	---------------------------------------------
//	offset calculated in accordance to the camera
void	init_translation_m(t_vec3 camera_position, double translation_m[4][4])
{
	ft_bzero(translation_m, 4 * 4 * sizeof(double));
	translation_m[0][0] = 1;
	translation_m[0][3] = -camera_position.e[0];
	translation_m[1][1] = 1;
	translation_m[1][3] = -camera_position.e[1];
	translation_m[2][2] = 1;
	translation_m[2][3] = -camera_position.e[2];
	translation_m[3][3] = 1;
}

//
//	ROTATION_X	MATRIX
//	{	1		0			0		0	}
//	{	0	cos(rad)	sin(rad)	0	}
//	{	0	-sin(rad)	cos(rad)	0	}
//	{	0		0			0		1	}
//	--------------------------------------
void	init_x_rotation_m(double rad, double rotation_x_m[4][4])
{
	ft_bzero(rotation_x_m, 4 * 4 * sizeof(double));
	rotation_x_m[0][0] = 1;
	rotation_x_m[1][1] = cos(rad);
	rotation_x_m[1][2] = sin(rad);
	rotation_x_m[2][1] = -sin(rad);
	rotation_x_m[2][2] = cos(rad);
	rotation_x_m[3][3] = 1;
}

//
//	ROTATION_Y	MATRIX
//	{	cos(rad)	0	-sin(rad)	0	}
//	{		0		1		0		0	}
//	{	sin(rad)	0	cos(rad)	0	}
//	{		0		0		0		1	}
//	--------------------------------------
void	init_y_rotation_m(double rad, double rotation_y_m[4][4])
{
	ft_bzero(rotation_y_m, 4 * 4 * sizeof(double));
	rotation_y_m[0][0] = cos(rad);
	rotation_y_m[0][2] = -sin(rad);
	rotation_y_m[1][1] = 1;
	rotation_y_m[2][0] = sin(rad);
	rotation_y_m[2][2] = cos(rad);
	rotation_y_m[3][3] = 1;
}

void	matrix_matrix_mult(double mtrx1[4][4], double mtrx2[4][4], double result_m[4][4])
{
	int		row;
	int		col;
	int		n_col;

	ft_bzero(result_m, 4 * 4 * sizeof(double));
	row = 0;
	while (row < 4)
	{
		n_col = 0;
		while (n_col < 4)
		{
			col = 0;
			while (col < 4)
			{
				result_m[row][n_col] += (mtrx2[row][col] * mtrx1[col][n_col]);
				col++;
			}
			n_col++;
		}
		row++;
	}
}

void	matrix_vector_mult(double matrix[4][4], double vector[4], double result_v[4])
{
	int		row;
	int		col;


	ft_bzero(result_v, 4 * sizeof(double));
	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			result_v[row] += (matrix[row][col] * vector[col]);
			col++;
		}
		row++;
	}
}

// //
// //	ROTATION_Z	MATRIX
// //	{	cos(rad)	-sin(rad)	0	0	}
// //	{	sin(rad)	cos(rad)	0	0	}
// //	{		0			0		1	0	}
// //	{		0			0		0	1	}
// //	---------------------------------------
// void	init_z_rotation_m(double rad, double rotation_z_m[4][4])
// {
// 	// double	rad;
//
// 	// rad = degree / 180 * M_PI;
//
// 	ft_bzero(&rotation_z_m, 4 * 4 * sizeof(double));
// 	rotation_z_m[0][0] = cos(rad);
// 	rotation_z_m[0][1] = -sin(rad);
// 	rotation_z_m[1][0] = sin(rad);
// 	rotation_z_m[1][1] = cos(rad);
// 	rotation_z_m[2][2] = 1;
// 	rotation_z_m[3][3] = 1;
// }
