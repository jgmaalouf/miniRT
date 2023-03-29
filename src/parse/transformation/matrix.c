/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:26:20 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/29 08:06:54 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

#include <math.h>

// //	TRANSLATION	MATRIX
// //	{	1	0	0	offset_x	}
// //	{	0	1	0	offset_y	}
// //	{	0	0	1		0		}
// //	{	0	0	0		1		}
// //	--------------------------------------------------------
// //	offset calculated automatically in accordance to the map
// double	**init_translation_m(t_vec3 camera_position)
// {
// 	double	translation_m[4][4];

// 	ft_bzero(&translation_m, 4 * 4 * sizeof(double));
// 	translation_m[0][0] = 1;
// 	translation_m[0][3] = camera_position.e[0];
// 	translation_m[1][1] = 1;
// 	translation_m[1][3] = camera_position.e[1];
// 	translation_m[2][2] = 1;
// 	translation_m[2][3] = camera_position.e[2];
// 	translation_m[3][3] = 1;
// 	return (translation_m);
// }

// //
// //	ROTATION_X	MATRIX
// //	{	1		0			0		0	}
// //	{	0	cos(rad)	sin(rad)	0	}
// //	{	0	-sin(rad)	cos(rad)	0	}
// //	{	0		0			0		1	}
// //	--------------------------------------
// double	**init_x_rotation_m(double rad)
// {
// 	// double	rad;

// 	// rad = degree / 180 * M_PI;
// 	double	rotation_x_m[4][4];

// 	ft_bzero(&rotation_x_m, 4 * 4 * sizeof(double));
// 	rotation_x_m[0][0] = 1;
// 	rotation_x_m[1][1] = cos(rad);
// 	rotation_x_m[1][2] = sin(rad);
// 	rotation_x_m[2][1] = -sin(rad);
// 	rotation_x_m[2][2] = cos(rad);
// 	rotation_x_m[3][3] = 1;
// 	return (rotation_x_m);
// }

// //
// //	ROTATION_Y	MATRIX
// //	{	cos(rad)	0	-sin(rad)	0	}
// //	{		0		1		0		0	}
// //	{	sin(rad)	0	cos(rad)	0	}
// //	{		0		0		0		1	}
// //	--------------------------------------
// double	**init_y_rotation_m(double rad)
// {
// 	// double	rad;

// 	// rad = degree / 180 * M_PI;
// 	double	rotation_y_m[4][4];

// 	ft_bzero(&rotation_y_m, 4 * 4 * sizeof(double));
// 	rotation_y_m[0][0] = cos(rad);
// 	rotation_y_m[0][2] = -sin(rad);
// 	rotation_y_m[1][1] = 1;
// 	rotation_y_m[2][0] = sin(rad);
// 	rotation_y_m[2][2] = cos(rad);
// 	rotation_y_m[3][3] = 1;
// 	return (rotation_y_m);
// }

// //
// //	ROTATION_Z	MATRIX
// //	{	cos(rad)	-sin(rad)	0	0	}
// //	{	sin(rad)	cos(rad)	0	0	}
// //	{		0			0		1	0	}
// //	{		0			0		0	1	}
// //	---------------------------------------
// double	**init_z_rotation_m(double rad)
// {
// 	// double	rad;

// 	// rad = degree / 180 * M_PI;
// 	double	rotation_z_m[4][4];

// 	ft_bzero(&rotation_z_m, 4 * 4 * sizeof(double));
// 	rotation_z_m[0][0] = cos(rad);
// 	rotation_z_m[0][1] = -sin(rad);
// 	rotation_z_m[1][0] = sin(rad);
// 	rotation_z_m[1][1] = cos(rad);
// 	rotation_z_m[2][2] = 1;
// 	rotation_z_m[3][3] = 1;
// 	return (rotation_z_m);
// }
