/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:36:08 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/29 18:15:43 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "scene.h"
#include <stdint.h>
#include <stdio.h>

uint32_t	to_rgba(uint8_t red, uint8_t green, uint8_t blue)
{
	return ((uint32_t)(red << 24 | green << 16 | blue << 8 | 0xFF));
}

uint32_t	translate_colors(double r, double g, double b)
{
	uint8_t	ir;
	uint8_t	ig;
	uint8_t	ib;

	ir = (uint8_t)(256 * clamp(r, 0.0, 0.999));
	ig = (uint8_t)(256 * clamp(g, 0.0, 0.999));
	ib = (uint8_t)(256 * clamp(b, 0.0, 0.999));
	return (to_rgba(ir, ig, ib));
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

/*
	Clamps the value x to the range [min,max]
*/
double	clamp(double x, double min, double max)
{
	x = clamp_min(x, min);
	x = clamp_max(x, max);
	return x;
}
