/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:50:52 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/13 16:04:55 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
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

	// printf("r: %f\tg: %f\tb: %f\n", r, g, b);

	ir = (uint8_t)(256 * clamp(r, 0.0, 0.999));
	ig = (uint8_t)(256 * clamp(g, 0.0, 0.999));
	ib = (uint8_t)(256 * clamp(b, 0.0, 0.999));
	return (to_rgba(ir, ig, ib));
}