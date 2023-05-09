/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearResource.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:46:52 by moulmoud          #+#    #+#             */
/*   Updated: 2023/05/09 23:37:47 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "philo.h"

void	clearresource(t_philo *philos)
{
	t_philo	*tmp;
	int		num_philo;

	pthread_mutex_destroy(&philos->monitor->dead);
	pthread_mutex_destroy(&philos->monitor->eating);
	pthread_mutex_destroy(&philos->monitor->print);
	free(philos->monitor);
	num_philo = philos->monitor->nb_philos;
	while (num_philo--)
	{
		tmp = philos;
		philos = philos->next;
		pthread_mutex_destroy(&tmp->fork);
		pthread_mutex_destroy(&tmp->last_eat_mutex);
		philos->monitor = NULL;
		free(tmp);
	}
}
