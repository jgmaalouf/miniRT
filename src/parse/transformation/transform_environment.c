/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_environment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:15:39 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/30 04:02:38 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "scene.h"
#include "matrix.h"

#include <stdio.h>
#include <math.h>

void print_matrix(double A[4][4])
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%.2lf ", A[i][j]);
        }
        printf("\n");
    }
        printf("\n");
}

double	get_x_rotation(t_vec3 cam_orient)
{
	t_vec3	cam_default;
	double	dot_product;
	double	v_proj_len;

	cam_default = vec3_constr(0, 0, -1);
	dot_product = vec3_dot(cam_default, cam_orient);
	v_proj_len = sqrt(
		cam_default.e[0] * cam_default.e[0]
		+ cam_orient.e[1] * cam_orient.e[1]
		);
	return (atan2(cam_default.e[2], dot_product / v_proj_len));
}

double	get_y_rotation(t_vec3 cam_orient)
{
	t_vec3	cam_default;
	double	cos_angle;
	double	dot_product;

	cam_default = vec3_constr(0, 0, -1);
	dot_product = cam_default.e[0] * cam_orient.e[0] + cam_default.e[2] * cam_orient.e[2];
	cos_angle = dot_product
		/ sqrt(
			(cam_default.e[0] * cam_orient.e[0]
			+ cam_default.e[2] * cam_orient.e[2])
			* (cam_default.e[0] * cam_orient.e[0]
			+ cam_default.e[2] * cam_orient.e[2])
			);
	return (acos(cos_angle));
	
}

void	get_camera_to_world_matrix(t_camera camera, double c_to_w[4][4])
{
	double	temp[4][4];
	double	x_rot_m[4][4];
	double	y_rot_m[4][4];

	init_translation_m(camera.pos, c_to_w);
	if (camera.orient.e[0] || camera.orient.e[2])
	{
		init_y_rotation_m(get_y_rotation(camera.orient), y_rot_m);
		// print_matrix(y_rot_m);
		ft_bzero(temp, 4 * 4 * sizeof(double));
		matrix_matrix_mult(c_to_w, y_rot_m, temp);
		ft_memcpy(c_to_w, temp, 4 * 4 * sizeof(double));
	}
	if (camera.orient.e[1])
	{
		init_x_rotation_m(get_x_rotation(camera.orient), x_rot_m);
		// print_matrix(x_rot_m);
		ft_bzero(temp, 4 * 4 * sizeof(double));
		matrix_matrix_mult(c_to_w, x_rot_m, temp);
		ft_memcpy(c_to_w, temp, 4 * 4 * sizeof(double));
	}
}

void invert_matrix(double matrix[4][4], double inverse[4][4]) {
    double augment[4][8];
    int i = 0;
    int j = 0;

    // Initialize the augmented matrix
    while (i < 4) {
        j = 0;
        while (j < 8) {
            if (j < 4) {
                augment[i][j] = matrix[i][j];
            } else {
                augment[i][j] = (j == i + 4) ? 1 : 0;
            }
            j++;
        }
        i++;
    }

    // Perform row operations to get the identity matrix on the left side
    i = 0;
    j = 0;
    while (i < 4 && j < 8) {
        // Find the row with the largest absolute value in the current column
        int k = i;
        double max_abs = 0;
        while (k < 4) {
            if (augment[k][j] < 0) {
                augment[k][j] = -augment[k][j];
            }
            if (augment[k][j] > max_abs) {
                max_abs = augment[k][j];
                i = k;
            }
            k++;
        }

        if (max_abs > 0) {
            // Swap the current row with the row with the largest absolute value
            int l = 0;
            while (l < 8) {
                double temp = augment[i][l];
                augment[i][l] = augment[k][l];
                augment[k][l] = temp;
                l++;
            }

            // Scale the current row to make the pivot element 1
            double temp = augment[i][j];
        	l = 0;
            while (l < 8) {
                augment[i][l] /= temp;
                l++;
            }

            // Perform row operations to make all other elements in the current column 0
            k = 0;
            while (k < 4) {
                if (k != i) {
                    temp = augment[k][j];
                    int l = 0;
                    while (l < 8) {
                        augment[k][l] -= temp * augment[i][l];
                        l++;
                    }
                }
                k++;
            }

            i++;
        }

        j++;
    }

    // Copy the inverse matrix from the augmented matrix
    i = 0;
    while (i < 4) {
        int j = 0;
        while (j < 4) {
            inverse[i][j] = augment[i][j + 4];
            j++;
        }
        i++;
    }
}

// void inverse_matrix(double A[4][4], double A_inv[4][4])
// {
// 	// initialize the augmented matrix [A|I]
// 	double B[4][2*4];
// 	int i = 0;
// 	while (i < 4) {
// 		int j = 0;
// 		while (j < 4) {
// 			B[i][j] = A[i][j];
// 			j++;
// 		}
// 		int k = 4;
// 		while (k < 2*4) {
// 			B[i][k] = (k == i + 4) ? 1.0 : 0.0;
// 			k++;
// 		}
// 		i++;
// 	}
		
// 	// apply Gauss-Jordan elimination
// 	int i1 = 0;
// 	while (i1 < 4) {
// 		double pivot = B[i1][i1];
// 		int j1 = i1;
// 		while (j1 < 2*4) {
// 			B[i1][j1] /= pivot;
// 			j1++;
// 		}
// 		int k1 = 0;
// 		while (k1 < 4) {
// 			if (k1 != i1) {
// 				double factor = B[k1][i1];
// 				int j2 = i1;
// 				while (j2 < 2*4) {
// 					B[k1][j2] -= factor * B[i1][j2];
// 					j2++;
// 				}
// 			}
// 			k1++;
// 		}
// 		i1++;
// 	}
		
// 	// extract the inverse matrix from the augmented matrix
// 	int i2 = 0;
// 	while (i2 < 4) {
// 		int j3 = 0;
// 		while (j3 < 4) {
// 			A_inv[i2][j3] = B[i2][j3 + 4];
// 			j3++;
// 		}
// 		i2++;
// 	}
// }


void	scene_elements_transform(t_scene *scene)
{
	double	c_to_w[4][4];
	double	w_to_c[4][4];

	get_camera_to_world_matrix(scene->camera, c_to_w);
	print_matrix(c_to_w);
	invert_matrix(c_to_w, w_to_c);
	print_matrix(w_to_c);
	// apply_world_to_camera_matrix(scene, w_to_c);
}
