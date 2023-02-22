#ifndef ERRORS_H
# define ERRORS_H

# include "minirt.h"

# define INVALID_ARGS	0
# define INVALID_FILE	1

# define RATIO			2
# define COORD			3
# define ORIENT			4
# define FOV			5
# define SIZE			6
# define RGB			7
# define ELEM			8
# define UNKNOWN		9

# define MORE			9
# define LESS			10


int	inval_input(int type);

int	inval_amount(int type, char *str);

void	panic(char *str);

bool	inval_arg(int type, char *str);

#endif
