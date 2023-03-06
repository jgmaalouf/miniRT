/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:41:02 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/06 19:55:19 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elem_count.h"

t_elem_count	*elem_count(void)
{
	static t_elem_count	count;

	return (&count);
}

int	get_count(enum type t_type)
{
	t_elem_count	*count;

	count = elem_count();
	if (t_type == cameras)
		return (count->cam_count);
	if (t_type == amb_lights)
		return (count->a_li_count);
	if (t_type == lights)
		return (count->li_count);
	if (t_type == spheres)
		return (count->sp_count);
	if (t_type == planes)
		return (count->pl_count);
	if (t_type == cylinders)
		return (count->cy_count);
	return (-1);
}

void	incr_count(enum type t_type)
{
	t_elem_count	*count;

	count = elem_count();
	if (t_type == cameras)
		count->cam_count++;
	else if (t_type == amb_lights)
		count->a_li_count++;
	else if (t_type == lights)
		count->li_count++;
	else if (t_type == spheres)
		count->sp_count++;
	else if (t_type == planes)
		count->pl_count++;
	else if (t_type == cylinders)
		count->cy_count++;
}
