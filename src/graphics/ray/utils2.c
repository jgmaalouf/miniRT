/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:36:08 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/13 15:18:52 by amorvai          ###   ########.fr       */
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

// clamps the value x to the range [min,max]
double	clamp(double x, double min, double max)
{
	if (x < min)
		return min;
	if (x > max)
		return max;
	return x;
}
