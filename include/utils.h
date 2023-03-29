/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:55 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/29 18:24:39 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>

double		clamp_min(double x, double min);
double		clamp_max(double x, double max);
double		clamp(double x, double min, double max);
uint32_t	translate_colors(double r, double g, double b);

#endif
