/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:55 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/16 20:02:48 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "ray.h"
# include "vector.h"

double		random_double();
double		random_double_in(double min, double max);
double		clamp(double x, double min, double max);

#endif