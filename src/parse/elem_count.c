/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:41:02 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/30 19:12:13 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elem_count.h"
#include "parse.h"

t_elem_count	*elem_count(void)
{
	static t_elem_count	count;

	return (&count);
}

size_t	get_count(uint8_t elem_type, t_scene *scene)
{
	t_elem_count	*count;

	count = elem_count();
	if (elem_type == g_camera)
		return (count->cam_count);
	if (elem_type == g_amb_light)
		return (count->a_li_count);
	if (elem_type == g_light)
		return (count->li_count);
	if (elem_type == g_sphere)
		return (scene->hittable.sp_count);
	if (elem_type == g_plane)
		return (scene->hittable.pl_count);
	if (elem_type == g_cylinder)
		return (scene->hittable.cy_count);
	return (-1);
}

void	incr_count(uint8_t elem_type, t_scene *scene)
{
	t_elem_count	*count;

	count = elem_count();
	if (elem_type == g_camera)
		count->cam_count++;
	else if (elem_type == g_amb_light)
		count->a_li_count++;
	else if (elem_type == g_light)
		count->li_count++;
	else if (elem_type == g_sphere)
		scene->hittable.sp_count++;
	else if (elem_type == g_plane)
		scene->hittable.pl_count++;
	else if (elem_type == g_cylinder)
		scene->hittable.cy_count++;
}
