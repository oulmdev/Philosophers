/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startSimulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:32:31 by moulmoud          #+#    #+#             */
/*   Updated: 2023/05/07 22:56:49 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "philo.h"

bool	print_it(t_philo *philo, char *str)
{
	pthread_mutex_lock(&((t_monitor *)philo->monitor)->dead);
	pthread_mutex_lock(&((t_monitor *)philo->monitor)->print);
	if (((t_monitor *)philo->monitor)->is_dead == true )
	{
		pthread_mutex_unlock(&((t_monitor *)philo->monitor)->dead);
		pthread_mutex_unlock(&((t_monitor *)philo->monitor)->print);
		return (false);
	}
	printf("%ld %d %s\n", get_time() - ((t_monitor *)philo->monitor)->start_time, philo->id, str);
	pthread_mutex_unlock(&((t_monitor *)philo->monitor)->print);
	pthread_mutex_unlock(&((t_monitor *)philo->monitor)->dead);
	return (true);
}

void	ft_usleep(long time, t_philo *philo)
{
	long	start;


	start = get_time();
	while (get_time() - start < time)
	{
		usleep(100);
		pthread_mutex_lock(&((t_monitor *)philo->monitor)->dead);
		if (((t_monitor *)philo->monitor)->is_dead == true)
		{
			pthread_mutex_unlock(&((t_monitor *)philo->monitor)->dead);
			return ;
		}
		pthread_mutex_unlock(&((t_monitor *)philo->monitor)->dead);
	}
}

bool	check_full(t_philo *philo)
{
	pthread_mutex_lock(&((t_monitor *)philo->monitor)->eating);
	if (((t_monitor *)philo->monitor)->nb_eat != -1)
	{
		pthread_mutex_unlock(&((t_monitor *)philo->monitor)->eating);
		return (true);
	}
	if (philo->eat_count == ((t_monitor *)philo->monitor)->nb_eat && ((t_monitor *)philo->monitor)->nb_eat != -1)
	{
		pthread_mutex_unlock(&((t_monitor *)philo->monitor)->eating);
		return (false);

	}
	pthread_mutex_unlock(&((t_monitor *)philo->monitor)->eating);
	return (true);
}

void	*routine(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	while (1)
	{
		pthread_mutex_lock(&tmp->fork);
		if (print_it(tmp, "has taken a fork") == false || (tmp->id == 1 && tmp->next->id == 1))
		{
			if (tmp->id == 1 && tmp->next->id == 1)
			{
				ft_usleep(((t_monitor *)tmp->monitor)->time_to_die, tmp);
				print_it(tmp, "died");
			}
			pthread_mutex_unlock(&tmp->fork);
			break ;
		}
		pthread_mutex_lock(&tmp->next->fork);
		if (print_it(tmp, "has taken a fork") == false)
			return (pthread_mutex_unlock(&tmp->fork), pthread_mutex_unlock(&tmp->next->fork), NULL);
		if (print_it(tmp, "is eating") == false)
		{
			pthread_mutex_unlock(&tmp->fork);
			pthread_mutex_unlock(&tmp->next->fork);
			break ;
		}
		pthread_mutex_lock(&(tmp->last_eat_mutex));
		tmp->last_eat = get_time();
		pthread_mutex_unlock(&(tmp->last_eat_mutex));
		if (((t_monitor *)tmp->monitor)->nb_eat != -1)
			tmp->eat_count++ ;
		ft_usleep(((t_monitor *)tmp->monitor)->time_to_eat, tmp);
		pthread_mutex_unlock(&tmp->fork);
		pthread_mutex_unlock(&tmp->next->fork);
		if (tmp->eat_count == ((t_monitor *)tmp->monitor)->nb_eat)
		{
			pthread_mutex_unlock(&((t_monitor *)tmp->monitor)->eating);
			tmp->is_full = true;
			break ;
		}
		if (print_it(tmp, "is sleeping") == false)
			break ;
		ft_usleep(((t_monitor *)tmp->monitor)->time_to_sleep, tmp);
		if (print_it(tmp, "is thinking") == false)
			break ;
	}
	return (NULL);
}

void	*monitor(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	while (1)
	{
		pthread_mutex_lock(&((t_monitor *)tmp->monitor)->dead);
		if (((t_monitor *)tmp->monitor)->is_dead == true)
		{
			pthread_mutex_unlock(&((t_monitor *)tmp->monitor)->dead);
			break ;
		}
		pthread_mutex_lock(&(tmp->last_eat_mutex));
		if (get_time() - tmp->last_eat
			> ((t_monitor *)tmp->monitor)->time_to_die
			&& (t_monitor *)tmp->monitor->is_dead == false)
		{

			pthread_mutex_unlock(&((t_monitor *)tmp->monitor)->dead);
			print_it(tmp, "died");
			pthread_mutex_lock(&((t_monitor *)tmp->monitor)->dead);
			((t_monitor *)tmp->monitor)->is_dead = true;
			pthread_mutex_unlock(&((t_monitor *)tmp->monitor)->dead);
			pthread_mutex_unlock(&(tmp->last_eat_mutex));
			break ;
		}
		pthread_mutex_unlock(&((t_monitor *)tmp->monitor)->dead);
		pthread_mutex_unlock(&(tmp->last_eat_mutex));
		usleep(100);
	}
	return (NULL);

}

bool	start_simulation(t_philo *philos)
{
	t_philo		*tmp;
	int			nb_philos;
	pthread_t	monitor_thread;


	tmp = philos;
	nb_philos = ((t_monitor *)tmp->monitor)->nb_philos;
	while (nb_philos--)
	{
		if (pthread_create(&tmp->thread, NULL, routine, tmp))
			return (false);
		if (!(tmp->id == 1 && tmp->next->id == 1))
		{
			if (pthread_create(&monitor_thread, NULL, monitor, tmp))
				return (false);
			pthread_detach(monitor_thread);
		}
		usleep(100);
		tmp = tmp->next;
	}
	tmp = philos;
	nb_philos = ((t_monitor *)philos->monitor)->nb_philos;
	while (nb_philos--)
	{
		if (pthread_join(tmp->thread, NULL))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}
