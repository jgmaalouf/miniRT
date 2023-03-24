/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:10 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/24 17:27:38 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "scene.h"

# define TOK_COORD 0b1000000
# define TOK_ORIENT 0b100000
# define TOK_FOV 0b10000
# define TOK_RATIO 0b1000
# define TOK_DIAMETER 0b100
# define TOK_HEIGHT 0b10
# define TOK_RGB 0b1

// As these are static const they are not considered "global" by the norm

static const uint8_t	g_amb_light = TOK_RATIO | TOK_RGB;
static const uint8_t	g_camera = TOK_COORD | TOK_ORIENT | TOK_FOV;
static const uint8_t	g_light = TOK_COORD | TOK_RATIO | TOK_RGB;
static const uint8_t	g_sphere = TOK_COORD | TOK_DIAMETER | TOK_RGB;
static const uint8_t	g_plane = TOK_COORD | TOK_ORIENT | TOK_RGB;
static const uint8_t	g_cylinder = TOK_COORD | TOK_ORIENT
	| TOK_DIAMETER | TOK_HEIGHT | TOK_RGB;

// Szenenfüllung

void	fill_elem(t_scene *scene, char *str);

void	fill_amb_light(char *str, t_scene *scene);
void	fill_camera(char *str, t_scene *scene);
void	fill_light(char *str, t_scene *scene);
void	fill_sphere(char *str, t_scene *scene);
void	fill_plane(char *str, t_scene *scene);
void	fill_cylinder(char *str, t_scene *scene);

typedef void	(*t_filler)(char *str, t_scene *scene);

static struct a
{
	char		*elem;
	size_t		elem_len;
	t_filler	filler;
} filler[] =
	{
		{"A", 1, fill_amb_light},
		{"C", 1, fill_camera},
		{"L", 1, fill_light},
		{"sp", 2, fill_sphere},
		{"pl", 2, fill_plane},
		{"cy", 2, fill_cylinder}
	};


// Szenenvalidierung

bool	valid_elem(char *str, t_scene *scene);
void	valid_elem_info(uint8_t elem_type, char **str, bool *ero_bewliun);
bool	valid_elem_count(t_scene *scene);

bool	valid_coord(char **str);
bool	valid_orient(char **str);
bool	valid_fov(char **str);
bool	valid_ratio(char **str);
bool	valid_dbl_size(char **str);
bool	valid_rgb(char **str);

// Nutzen

void	skip_spaces(char **str);
void	increment_while_double(char **str);

void	fill_single_val(char **str, double *val);
void	fill_triple_val(char **str, t_vec3 *triple_val);

#endif
