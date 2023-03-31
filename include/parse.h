/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:10 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/31 16:47:20 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h> // bool
# include <stdint.h> // uint8_t
# include <stdlib.h> // size_t
# include <float.h> // DBL_MAX

# include "scene.h"
# include "vector.h"

// _____________________________________________________________________________
//
//	Szenenvalidierung
// _____________________________________________________________________________

bool	validate_element(char *str, t_scene *scene, size_t line);
uint8_t	validate_element_info(char **str, uint8_t element_bitmask);
bool	validate_element_count(t_scene *scene);

bool	validate_single_val(char **str, const double min, const double max);
bool	validate_triple_val(char **str, const double min, const double max);

typedef bool			(*t_valid_val)(char **, const double, const double);

static const struct s_validate
{
	uint8_t		token;
	t_valid_val	validater;
	double		min;
	double		max;
	char		*error_message;
}
p[] = {
{TOK_COORD,		validate_triple_val,	0,		0,
"\tThe coordinates for the %s are invalid!\n"},
{TOK_ORIENT,	validate_triple_val,	-1,		1,
"\tThe orientation vector for the %s is invalid!\n"},
{TOK_FOV,		validate_single_val,	0,		180,
"\tThe FOV value for the %s is invalid!\n"},
{TOK_RATIO,		validate_single_val,	0,		1,
"\tThe %s ratio is invalid!\n"},
{TOK_DIAMETER,	validate_single_val,	0,		DBL_MAX,
"\tThe %s diameter is invalid!\n"},
{TOK_HEIGHT,	validate_single_val,	0,		DBL_MAX,
"\tThe %s height is invalid!\n"},
{TOK_ANGLE,		validate_single_val,	0,		89,
"\tThe %s angle is invalid!\n"},
{TOK_RGB,		validate_triple_val,	0,		255,
"\tThe RGB value for %s is invalid!\n"}
};

// _____________________________________________________________________________
//
//	Szenenfüllung
// _____________________________________________________________________________

void	fill_element(t_scene *scene, char *str);

void	fill_amb_light(char *str, t_scene *scene);
void	fill_camera(char *str, t_scene *scene);
void	fill_light(char *str, t_scene *scene);
void	fill_sphere(char *str, t_scene *scene);
void	fill_plane(char *str, t_scene *scene);
void	fill_cylinder(char *str, t_scene *scene);
void	fill_cone(char *str, t_scene *scene);

typedef void			(*t_filler)(char *str, t_scene *scene);

static const t_filler	g_element_fillers[] = {
	fill_amb_light,
	fill_camera,
	fill_light,
	fill_sphere,
	fill_plane,
	fill_cylinder,
	fill_cone
};

// _____________________________________________________________________________
//
//	Nutzen
// _____________________________________________________________________________

void	skip_spaces(char **str);
void	increment_while_double(char **str);

void	fill_single_val(char **str, double *val);
void	fill_triple_val(char **str, t_vec3 *triple_val);

// _____________________________________________________________________________

#endif
