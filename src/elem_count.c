#include "elem_count.h"

t_elem_count *elem_count()
{
	static t_elem_count count;

	return (&count);
}

int	get_count(enum type e_type)
{
	t_elem_count *count;

	count = arr_size();
	if (e_type == cameras)
		return (count->cam_count);
	if (e_type == amb_lights)
		return (count->a_li_count);
	if (e_type == lights)
		return (count->li_count);
	if (e_type == spheres)
		return (count->sp_count);
	if (e_type == planes)
		return (count->pl_count);
	if (e_type == cylinders)
		return (count->cy_count);
	return (-1);
}

void	set_count(enum type e_type, int size)
{
	t_elem_count *count;

	count = arr_size();
	if (e_type == cameras)
		count->cam_count = size;
	else if (e_type == amb_lights)
		count->a_li_count = size;
	else if (e_type == lights)
		count->li_count = size;
	else if (e_type == spheres)
		count->sp_count = size;
	else if (e_type == planes)
		count->pl_count = size;
	else if (e_type == cylinders)
		count->cy_count = size;
}
