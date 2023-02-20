#include "validation.h"

int invalid_input(int type)
{
	if (type == INVALID_ARGS)
		printf("%s\n", "Not enough args!");
	return(EXIT_FAILURE);
}
