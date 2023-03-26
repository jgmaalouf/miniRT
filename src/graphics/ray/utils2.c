/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:36:08 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/24 14:11:29 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // rand()

// Returns a random real in [0,1).
double	random_double()
{
	return ((double)rand() / (double)RAND_MAX + 1.0);
}

// Returns a random real in [min,max).
double	random_double_in(double min, double max)
{
	return (min + (max - min) * random_double());
}

double	clamp_min(double x, double min)
{
	if (x < min)
		return min;
	return x;
}

double	clamp_max(double x, double max)
{
	if (x > max)
		return max;
	return x;
}

// clamps the value x to the range [min,max]
double	clamp(double x, double min, double max)
{
	// if (clamp_min(x, min) != x)
	// 	return (min);
	// if (clamp_max(x, max) != x)
	// 	return (max);
	x = clamp_min(x, min);
	x = clamp_max(x, max);
	return x;
}
