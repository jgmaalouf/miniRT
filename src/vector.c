#include "vector.h"

t_vec3	vec3_constr(const double e0, const double e1, const double e2)
{
	t_vec3	vec3;

	vec3.e[0] = e0;
	vec3.e[1] = e1;
	vec3.e[2] = e2;
	return (vec3);
}

t_vec3	vec3_add(const t_vec3 u, const t_vec3 v)
{
	return (vec3_constr(
			u.e[0] + v.e[0],
			u.e[1] + v.e[1],
			u.e[2] + v.e[2]));
}

t_vec3	vec3_substr(const t_vec3 u, const t_vec3 v)
{
	return (vec3_constr(
			u.e[0] - v.e[0],
			u.e[1] - v.e[1],
			u.e[2] - v.e[2]));
}

t_vec3	vec3_mult(const t_vec3 u, const t_vec3 v)
{
	return (vec3_constr(
			u.e[0] * v.e[0],
			u.e[1] * v.e[1],
			u.e[2] * v.e[2]));
}

t_vec3	vec3_div(const t_vec3 u, const t_vec3 v)
{
	return (vec3_constr(
			u.e[0] / v.e[0],
			u.e[1] / v.e[1],
			u.e[2] / v.e[2]));
}

double	vec3_dot(const t_vec3 u, const t_vec3 v)
{
	return (u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2]);
}

t_vec3	vec3_cross(const t_vec3 u, const t_vec3 v)
{
	return (vec3_constr(
			u.e[1] * v.e[2] - u.e[2] * v.e[1],
			u.e[2] * v.e[0] - u.e[0] * v.e[2],
			u.e[0] * v.e[1] - u.e[1] * v.e[0]));
}

t_vec3	vec3_scale_mult(const t_vec3 v, const double scale)
{
	return (vec3_constr(
			v.e[0] * scale,
			v.e[1] * scale,
			v.e[2] * scale));
}

t_vec3	vec3_scale_div(const t_vec3 v, const double scale)
{
	return (vec3_scale_mult(v, 1 / scale));
}

double	vec3_length_squared(const t_vec3 v)
{
	return (vec3_dot(v, v));
}

double	vec3_length(const t_vec3 v)
{
	return (sqrt(vec3_length_squared(v)));
}

t_vec3	vec3_unit(t_vec3 v)
{
	return (vec3_scale_div(v, vec3_length(v)));
}
