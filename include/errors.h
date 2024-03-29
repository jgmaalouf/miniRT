/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:03 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/26 08:34:49 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

# define INVALID_ARGS	0
# define INVALID_FILE	1

# define MORE			2
# define LESS			3

void	invalid_input(int type);
void	invalid_element(uint8_t error_type, char *elem_name, size_t line);
void	invalid_element_amount(int type, char *str);

void	panic(char *str);
void	panic_exit(char *str);

#endif
