/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_alloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 07:19:51 by amorvai           #+#    #+#             */
/*   Updated: 2023/03/31 18:02:58 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_ALLOC_H
# define MEMORY_ALLOC_H

# include "scene.h"

void	scene_elements_allocate(t_scene *scene);
void	free_scene_elements(t_scene *scene);

#endif
