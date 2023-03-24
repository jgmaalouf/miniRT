/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:55:20 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/21 09:32:23 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	get_sign(const char *str, size_t *i, int *sign)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

int	ft_atoi(const char *str, int *result)
{
	long	n;
	size_t	i;
	int		sign;

	i = 0;
	n = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	get_sign(str, &i, &sign);
	if (str[i] == '\0')
		return (1);
	while ('0' <= str[i] && str[i] <= '9')
	{
		n = (n * 10) + str[i] - '0';
		if (sign == 1 && n > 2147483647)
			return (1);
		else if (sign == -1 && n > 2147483648)
			return (1);
		i++;
	}
	if (str[i] != '\0')
		return (1);
	*result = (int)(n * sign);
	return (0);
}

int	ft_atoi_mod(const char *str, int *result)
{
	long	n;
	size_t	i;
	int		sign;

	i = 0;
	n = 0;
	sign = 1;
	get_sign(str, &i, &sign);
	if (str[i] == '\0' || ft_isspace(str[i]) || str[i] == ',')
		return (1);
	while ('0' <= str[i] && str[i] <= '9')
	{
		n = (n * 10) + str[i] - '0';
		if (sign == 1 && n > 2147483647)
			return (1);
		else if (sign == -1 && n > 2147483648)
			return (1);
		i++;
	}
	if (str[i] != '\0' && !ft_isspace(str[i]) && str[i] != ',')
		return (1);
	*result = (int)(n * sign);
	return (0);
}

// int main()
// {
// 	char *str = "2147483647";// "0";//
// 	int result;
// 	printf("atoi(%s) return: %i\tresult: %i\n"
// 	, str, ft_atoi(str, &result), result);
// 	return (0);
// }
