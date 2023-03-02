#include "validate_elem.h"

bool	valid_amb_light(char *str)
{
	str++;
	skip_spaces(&str);
	if (!valid_ratio(&str))
		return (inval_arg(RATIO, "ambient light"));
	skip_spaces(&str);
	if (!valid_rgb(&str))
		return (inval_arg(RGB, "ambient light"));
	if (!valid_eol(&str))
		return (inval_arg(ELEM, "ambient light"));
	incr_count(amb_lights);
	return (true);
}

bool	valid_camera(char *str)
{
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
	incr_count(cameras);
	return (true);
}

bool	valid_light(char *str)
{
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
	incr_count(lights);
	return (true);
}

bool	valid_sphere(char *str)
{
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
	incr_count(spheres);
	return (true);
}

bool	valid_plane(char *str)
{
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
	incr_count(planes);
	return (true);
}

bool	valid_cylinder(char *str)
{
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
	incr_count(cylinders);
	return (true);
}
