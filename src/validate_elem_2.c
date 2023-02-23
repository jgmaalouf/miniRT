#include "validate_elem.h"

int	ft_isnumber(char *s)
{
	if (*s == '+' || *s == '-')
		s++;
	while (ft_isdigit(*s++))
		if (*s == '\0' || ft_isspace(*s) || *s == ',')
			return (1);
	return (0);
}

int ft_isdouble(char *s)
{
	if (*s == '+' || *s == '-')
		s++;
	while (ft_isdigit(*s))
		s++;
	if (*s == '\0' || ft_isspace(*s) || *s == ',')
		return (1);
	if (*s == '.')
	{
		s++;
		while (ft_isdigit(*s++))
		{
			if (*s == '\0' || ft_isspace(*s) || *s == ',')
				return (1);
		}
	}
	return (0);
}

void	skip_spaces(char **str)
{
	while (ft_isspace(**str))
		(*str)++;
}

bool	valid_ratio(char **str)
{
	double	ratio;

	if (!ft_isdouble(*str))
		return (false);
	ratio = ft_atod(*str);
	while (ft_isdigit(**str) || **str == '.')
		(*str)++;
	if (ratio >= 0.0 && ratio <= 1.0)
		return (true);
	return (false);
}

bool	valid_coord(char **str)
{
	int	i;

	i = 3;
	while (i > 0)
	{
		if (!ft_isdouble(*str))
			return (false);
		while (ft_isdigit(**str) || **str == '.'
			|| **str == '+' || **str == '-')
			(*str)++;
		if (**str == ',')
			(*str)++;
		i--;
	}
	return (true);
}

bool	valid_orient(char **str)
{
	int		i;
	double	val;

	i = 3;
	while (i > 0)
	{
		if (!ft_isdouble(*str))
			return (false);
		val = ft_atod(*str);
		while (ft_isdigit(**str) || **str == '.'
			|| **str == '+' || **str == '-')
			(*str)++;
		if (val < -1.0 || val > 1.0)
			return (false);
		if (**str == ',')
			(*str)++;
		i--;
	}
	return (true);
}

bool	valid_fov(char **str)
{
	int	fov;

	if (!ft_isnumber(*str))
		return (false);
	if (ft_atoi(*str, &fov) == 1
		|| fov > 180 || fov < 0)
		return (false);
	while(ft_isdigit(**str))
		(*str)++;
	return (true);
}

bool	valid_dbl_size(char **str)
{
	double	diam;

	if (!ft_isdouble(*str))
			return (false);
	diam = ft_atod(*str);
	while (ft_isdigit(**str) || **str == '.'
		|| **str == '+' || **str == '-')
		(*str)++;
	if (diam < 0.0 || diam > MAXFLOAT)
		return (false);
	return (true);
}

bool	valid_rgb(char **str)
{
	int		i;
	int		val;

	i = 3;
	while (i > 0)
	{
		if (!ft_isnumber(*str))
			return (false);
		if (ft_atoi(*str, &val) == 1 || val > 255 || val < 0)
			return (false);
		while (ft_isdigit(**str)
			|| **str == '+' || **str == '-')
			(*str)++;
		if (**str == ',')
			(*str)++;
		i--;
	}
	return (true);
}

bool	valid_eol(char **str)
{
	skip_spaces(str);
	if (**str == '\0' || **str == '\n')
		return (true);
	return (false);
}
