#include "validate_elem.h"

bool	valid_amb_light(char *str)
{
	incr_count(amb_lights);
	str++;
	skip_spaces(&str);
	if (!valid_ratio(&str))
		return (inval_arg(RATIO, "ambient light"));
	skip_spaces(&str);
	if (!valid_rgb(&str))
		return (inval_arg(RGB, "ambient light"));
	if (!valid_eol(&str))
		return (inval_arg(ELEM, "ambient light"));
	return (true);
}

bool	valid_camera(char *str)
{
	incr_count(cameras);
	str++;
	skip_spaces(&str);
	if (!valid_coord(&str))
		return (inval_arg(COORD, "camera"));
	skip_spaces(&str);
	if (!valid_orient(&str))
		return (inval_arg(ORIENT, "camera"));
	skip_spaces(&str);
	if (!valid_fov(&str))
		return (inval_arg(FOV, "camera"));
	if (!valid_eol(&str))
		return (inval_arg(ELEM, "camera"));
	return (true);
}

bool	valid_light(char *str)
{
	incr_count(lights);
	str++;
	skip_spaces(&str);
	if (!valid_coord(&str))
		return (inval_arg(COORD, "light"));
	skip_spaces(&str);
	if (!valid_ratio(&str))
		return (inval_arg(RATIO, "light"));
	skip_spaces(&str);
	if (!valid_rgb(&str))
		return (inval_arg(RGB, "light"));
	if (!valid_eol(&str))
		return (inval_arg(ELEM, "light"));
	return (true);
}

bool	valid_sphere(char *str)
{
	incr_count(spheres);
	str += 2;
	skip_spaces(&str);
	if (!valid_coord(&str))
		return (inval_arg(COORD, "sphere"));
	skip_spaces(&str);
	if (!valid_dbl_size(&str))
		return (inval_arg(SIZE, "sphere diameter"));
	skip_spaces(&str);
	if (!valid_rgb(&str))
		return (inval_arg(RGB, "sphere"));
	if (!valid_eol(&str))
		return (inval_arg(ELEM, "sphere"));
	return (true);
}

bool	valid_plane(char *str)
{
	incr_count(planes);
	str += 2;
	skip_spaces(&str);
	if (!valid_coord(&str))
		return (inval_arg(COORD, "plane"));
	skip_spaces(&str);
	if (!valid_orient(&str))
		return (inval_arg(ORIENT, "plane"));
	skip_spaces(&str);
	if (!valid_rgb(&str))
		return (inval_arg(RGB, "plane"));
	if (!valid_eol(&str))
		return (inval_arg(ELEM, "plane"));
	return (true);
}

bool	valid_cylinder(char *str)
{
	incr_count(cylinders);
	str += 2;
	skip_spaces(&str);
	if (!valid_coord(&str))
		return (inval_arg(COORD, "cylinder"));
	skip_spaces(&str);
	if (!valid_orient(&str))
		return (inval_arg(ORIENT, "cylinder"));
	skip_spaces(&str);
	if (!valid_dbl_size(&str))
		return (inval_arg(SIZE, "cylinder diameter"));
	skip_spaces(&str);
	if (!valid_dbl_size(&str))
		return (inval_arg(SIZE, "cylinder height"));
	skip_spaces(&str);
	if (!valid_rgb(&str))
		return (inval_arg(RGB, "cylinder"));
	if (!valid_eol(&str))
		return (inval_arg(ELEM, "cylinder"));
	return (true);
}
