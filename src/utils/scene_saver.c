/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_saver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:31:26 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/31 15:45:52 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_saver.h"

t_scene	*saved_scene_handler(t_scene *scene)
{
	static t_scene	s_scene;

	if (scene != NULL)
		s_scene = *scene;
	return (&s_scene);
}
