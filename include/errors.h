/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:03 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/11 19:39:00 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

#include <stdint.h>
#include <stdbool.h>

# define INVALID_ARGS	0
# define INVALID_FILE	1

# define MORE			2
# define LESS			3

bool	inval_input(int type);
bool	inval_amount(int type, char *str);
bool	inval_arg(uint8_t error_type, uint8_t elem_type);
void	panic(char *str);
void	panic_exit(char *str);

#endif
