/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 21:05:00 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/30 03:06:16 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	matrix_matrix_mult(double mtrx1[4][4], double mtrx2[4][4], double result_m[4][4])
{
	int		row;
	int		col;
	int		n_col;

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

// int main()
// {
// 	double *result_m;
// 	double **m1;
// 	double *m2;

// 	m1 = alloc_matrix();
// 	if (!m1)
// 		return (1);
// 	m2 = ft_calloc(4, sizeof(double));
// 	if (!m2)
// 	{
// 		free_matrix(m1);
// 		return (1);
// 	}
// 	m1[0][0] = 1;
// 	m1[0][1] = 2;
// 	m1[0][2] = 3;
// 	m1[0][3] = 4;

// 	m1[1][0] = 12;
// 	m1[1][1] = 2;
// 	m1[1][2] = 9;
// 	m1[1][3] = 1;

// 	m1[2][0] = 2;
// 	m1[2][1] = 3;
// 	m1[2][2] = 1;
// 	m1[2][3] = 5;

// 	m1[3][0] = 2;
// 	m1[3][1] = 1;
// 	m1[3][2] = 3;
// 	m1[3][3] = 1;

// 	m2[0] = 3;
// 	m2[1] = 2;
// 	m2[2] = 0;
// 	m2[3] = 1;

// 	// m2[1][0] = 0;
// 	// m2[1][1] = 2;
// 	// m2[1][2] = 3;
// 	// m2[1][3] = 5;

// 	// m2[2][0] = 0;
// 	// m2[2][1] = 2;
// 	// m2[2][2] = 1;
// 	// m2[2][3] = 2;

// 	// m2[3][0] = 1;
// 	// m2[3][1] = 1;
// 	// m2[3][2] = 1;
// 	// m2[3][3] = 1;
// 	result_m = matrix_vector_mult(m1, m2);
// 	free_matrix(m1);
// 	free(m2);
// 	if (result_m != NULL)
// 	{
// 	// print_matrix(result_m);
// 	// free_matrix(result_m);
// 	print_vector(result_m);
// 	free(result_m);
// 	}
// 	return (0);
// }
