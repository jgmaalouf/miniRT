/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_count.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:00 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/04/01 15:39:39 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEM_COUNT_H
# define ELEM_COUNT_H

# include <stdint.h>
# include "scene.h"

typedef struct s_elem_count
{
	size_t	cam_count;
	size_t	a_li_count;
	size_t	li_count;
}				t_elem_count;

t_elem_count	*elem_count(void);
size_t			get_count(uint8_t elem_type, const t_scene *scene);
void			incr_count(uint8_t elem_type, t_scene *scene);

#endif
