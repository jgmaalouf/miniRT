/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:40:08 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/03/10 19:46:49 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include "MLX42.h"
# include "lib.h"

# include "vector.h"
# include "ray.h"

# include "elem_count.h"
# include "errors.h"

# include "scene.h"

# include "parse.h"
# include "graphics.h"

void	print_scene(t_scene scene);
void	print_vec3(char *name, t_vec3 vec);

#endif
