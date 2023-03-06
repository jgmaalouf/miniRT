#ifndef ELEM_COUNT_H
# define ELEM_COUNT_H

enum	type
{
	cameras,
	amb_lights,
	lights,
	spheres,
	planes,
	cylinders
}		e_type;

typedef struct s_elem_count
{
	int	cam_count;
	int	a_li_count;
	int	li_count;
	int	sp_count;
	int	pl_count;
	int	cy_count;
}				t_elem_count;

t_elem_count	*elem_count(void);

int	get_count(enum type e_type);

void	incr_count(enum type e_type);

void	decr_count(enum type e_type);

#endif