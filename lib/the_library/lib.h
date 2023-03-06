/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 23:57:02 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/06 13:00:58 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "libft/libft.h"

int		ft_printf(const char *s, ...);
int		get_next_line(int fd, char **newline);

#endif
