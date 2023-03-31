/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:08 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/31 20:30:09 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "scene.h"
# include "vector.h"

void		print_scene(t_scene scene);
void		print_vec3(char *name, t_vec3 vec);

static void	print_amb_and_cam_and_light(t_scene scene);
static void	print_plane(t_scene scene);
static void	print_sphere(t_scene scene);
static void	print_cylinder(t_scene scene);
static void	print_cone(t_scene scene);

#endif
