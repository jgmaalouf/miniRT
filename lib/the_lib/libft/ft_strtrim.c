/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:13:59 by amorvai           #+#    #+#             */
/*   Updated: 2023/02/17 15:05:48 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_xstrtrim(const char *s1, const char *set)
{
	char	*ptr;

	ptr = ft_strtrim(s1, set);
	if (ptr)
		return (ptr);
	exit (-1);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*rtrn;
	size_t	i;
	size_t	j;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1);
	while (j > 0 && j > i && ft_strrchr(set, s1[j - 1]))
		j--;
	rtrn = ft_substr(s1, i, j - i);
	return (rtrn);
}
