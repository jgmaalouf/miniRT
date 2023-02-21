#ifndef ERRORS_H
# define ERRORS_H

# include "minirt.h"

# define INVALID_ARGS 0

int		invalid_input(int type);
int		too_much(char *str);
int		too_little(char *str);
void	panic(char *str);

#endif
