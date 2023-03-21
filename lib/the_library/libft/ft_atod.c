/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:21:54 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/21 09:49:21 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "libft.h"

static void	get_sign(const char *str, size_t *i, double *sign)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign *= -1.0;
		(*i)++;
	}
}

static int	get_double(const char *str, size_t *i, long double *val)
{
	double	dec;

	dec = 0.1;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		*val = *val * 10 + (str[*i] - '0');
		if (*val > DBL_MAX)
			return (1);
		(*i)++;
	}
	if (str[*i] == '.')
		(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		*val = *val + (dec * (str[*i] - '0'));
		dec *= 0.1;
		(*i)++;
	}
	return (0);
}

int	ft_atod(const char *str, double *res)
{
	long double	n;
	size_t		i;
	double		sign;

	i = 0;
	n = 0.0;
	sign = 1.0;
	while (ft_isspace(str[i]))
		i++;
	get_sign(str, &i, &sign);
	if (str[i] == '\0')
		return (1);
	if (get_double(str, &i, &n))
		return (1);
	if (str[i] != '\0')
		return (1);
	*res = n * sign;
	return (0);
}

int	ft_atod_mod(const char *str, double *res)
{
	long double	n;
	size_t		i;
	double		sign;

	i = 0;
	n = 0.0;
	sign = 1.0;
	get_sign(str, &i, &sign);
	if (str[i] == '\0' || ft_isspace(str[i]) || str[i] == ',')
		return (1);
	if (get_double(str, &i, &n))
		return (1);
	if (str[i] != '\0' && !ft_isspace(str[i]) && str[i] != ',')
		return (1);
	*res = (double)(n * sign);
	return (0);
}
