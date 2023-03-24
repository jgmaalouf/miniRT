/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:55 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/24 14:03:35 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

double		random_double();
double		random_double_in(double min, double max);
double		clamp_min(double x, double min);
double		clamp_max(double x, double max);
double		clamp(double x, double min, double max);

#endif
