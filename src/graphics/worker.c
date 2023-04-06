/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:34:11 by jmaalouf          #+#    #+#             */
/*   Updated: 2023/04/06 11:43:19 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "errors.h"

t_worker	*create_workers(t_scene *scene)
{
	size_t		i;
	t_worker	*workers;

	workers = malloc(sizeof(t_worker) * THREADS);
	if (workers == NULL)
		panic_exit("bad alloc");
	i = 0;
	while (i < THREADS)
	{
		workers[i].id = i;
		workers[i].scene = scene;
		i++;
	}
	return (workers);
}

void	join_threads(t_worker *workers)
{
	size_t	i;

	i = 0;
	while (i < THREADS)
	{
		pthread_join(workers[i].thread, NULL);
		i++;
	}
}

void	cancel_threads(t_worker *workers)
{
	size_t	i;

	i = 0;
	while (i < THREADS)
	{
		pthread_cancel(workers[i].thread);
		i++;
	}
}
