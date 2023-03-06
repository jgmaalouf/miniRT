/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:10 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/06 19:40:11 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minirt.h"

// Szenenfüllung
void	scene_populate(t_scene *scene, char *file);
void	fill_triple_val(char *str, t_vec3 *triple_val);
void	fill_amb_light(char *str, t_scene *scene);
void	fill_camera(char *str, t_scene *scene);
void	fill_light(char *str, t_scene *scene);
void	fill_sphere(char *str, t_scene *scene);

void	skip_spaces(char **str);

// Szenenvalidierung
bool	valid_amb_light(char *str);
bool	valid_camera(char *str);
bool	valid_light(char *str);
bool	valid_sphere(char *str);
bool	valid_plane(char *str);
bool	valid_cylinder(char *str);

bool	valid_ratio(char **str);
bool	valid_coord(char **str);
bool	valid_orient(char **str);
bool	valid_fov(char **str);
bool	valid_dbl_size(char **str);
bool	valid_rgb(char **str);
bool	valid_eol(char **str);

int		ft_isnumber(char *s);
int		ft_isdouble(char *s);
void	skip_spaces(char **str);
bool	valid_eol(char **str);

#endif
