/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:06:08 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/12 19:59:51 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

void	skip_spaces(char **str)
{
	while (ft_isspace(**str))
		(*str)++;
}

int	ft_isnumber(char *s)
{
	if (*s == '+' || *s == '-')
		s++;
	while (ft_isdigit(*s++))
		if (*s == '\0' || ft_isspace(*s) || *s == ',')
			return (1);
	return (0);
}

int	ft_isdouble(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	if (i > 10)
		return (0);
	if (s[i] == '\0' || ft_isspace(s[i]) || s[i] == ',')
		return (1);
	if (s[i] == '.')
	{
		i++;
		while (ft_isdigit(s[i++]))
		{
			if (s[i] == '\0' || ft_isspace(s[i]) || s[i] == ',')
				return (1);
			if (i > 10)
				return (0);
		}
	}
	return (0);
}

void	fill_triple_val(char *str, t_vec3 *triple_val)
{
	ft_atod(str, &triple_val->e[0]);
	while (ft_isdigit(*str) || *str == '.' || *str == '+' || *str == '-')
		str++;
	str++;
	ft_atod(str, &triple_val->e[1]);
	while (ft_isdigit(*str) || *str == '.' || *str == '+' || *str == '-')
		str++;
	str++;
	ft_atod(str, &triple_val->e[2]);
}
