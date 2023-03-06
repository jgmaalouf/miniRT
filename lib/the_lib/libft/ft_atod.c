/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:21:54 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/02 17:39:01 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>

// double	ft_atod(const char *str)
// {
// 	int		i;
// 	double	res;
// 	double	sign;
// 	double	dec;

// 	res = 0.0;
// 	sign = 1.0;
// 	dec = 0.1;
// 	i = 0;
// 	if (str[i] == '-' || str[i] == '+')
// 		if (str[i++] == '-')
// 			sign = -1.0;
// 	while (str[i] >= '0' && str[i] <= '9')
// 		res = res * 10 + (str[i++] - '0');
// 	if (str[i] == '.')
// 		i++;
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		res = res + (dec * (str[i++] - '0'));
// 		dec *= 0.1;
// 	}
// 	return (res * sign);
// }

static void	get_sign(const char *str, double *sign, int *i)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign *= -1.0;
		(*i)++;
	}
}

int	ft_atod(const char *str, double *res)
{
	int			i;
	long double	val;
	double		sign;
	double		dec;

	val = 0.0;
	sign = 1.0;
	dec = 0.1;
	i = 0;
	get_sign(str, &sign, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		val = val * 10 + (str[i++] - '0');
		if (val > DBL_MAX)
			return (0);
	}
	if (str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		val = val + (dec * (str[i++] - '0'));
		dec *= 0.1;
	}
	*res = val * sign;
	return (1);
}
