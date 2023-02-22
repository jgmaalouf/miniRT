#ifndef VALIDATE_ELEM_H
# define VALIDATE_ELEM_H

# include "minirt.h"

void	skip_spaces(char **str);
bool	valid_ratio(char **str);
bool	valid_coord(char **str);
bool	valid_orient(char **str);
bool	valid_fov(char **str);
bool	valid_dbl_size(char **str);
bool	valid_rgb(char **str);
bool	valid_eol(char **str);

bool	valid_amb_light(char *str);
bool	valid_camera(char *str);
bool	valid_light(char *str);
bool	valid_sphere(char *str);
bool	valid_plane(char *str);
bool	valid_cylinder(char *str);

#endif