/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_alloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 07:19:51 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/26 07:22:00 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_ALLOC_H
# define MEMORY_ALLOC_H

# include "scene.h"

void	scene_elements_allocate(t_scene *scene);

void	free_scene_elements(t_scene *scene);

#endif