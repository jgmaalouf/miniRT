/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:54:43 by amorvai           #+#    #+#             */
/*   Updated: 2023/02/17 14:36:47 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_xstrdup(const char *s1)
{
	char	*ptr;

	ptr = ft_strdup(s1);
	if (ptr)
		return (ptr);
	exit (-1);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*new;

	new = malloc(ft_strlen(s1) + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
