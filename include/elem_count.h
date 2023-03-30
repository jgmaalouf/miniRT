/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_count.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:00 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/31 01:15:26 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEM_COUNT_H
# define ELEM_COUNT_H

# include <stdint.h>
# include "scene.h"

typedef struct s_elem_count
{
	int	cam_count;
	int	a_li_count;
	int	li_count;
}				t_elem_count;

t_elem_count	*elem_count(void);
int				get_count(uint8_t elem_type, const t_scene *scene);
void			incr_count(uint8_t elem_type, t_scene *scene);

#endif