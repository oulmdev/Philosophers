/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:53:13 by moulmoud          #+#    #+#             */
/*   Updated: 2023/05/04 16:59:57 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (false);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
void	ft_usleep(long time)
{
	long long start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

bool	init_mutexes(t_philo *list)
{
	int		index;
	long	start_time;

	index = 0;
	start_time = get_time();
	if (!start_time)
		return (printf("Philo: Failed to get time.\n"), false);
	while (index < list->philo_count)
	{
		if (pthread_mutex_init(&list->fork, NULL))
			return (false);
		list->t_start = start_time;
		index++;
		list = list->next;
	}
	return (true);
}

void	print_it(t_philo *philo, char *message)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp->philo_id != 1)
		tmp = tmp->next;
	pthread_mutex_lock(&tmp->triger);
	printf("%ld philo %d %s", (get_time() - philo->t_start),
		philo->philo_id, message);
	pthread_mutex_unlock(&tmp->triger);
}

void	*routine(void *list)
{
	while (((t_philo *)list)->finished == false)
	{
		pthread_mutex_lock(&((t_philo *)list)->fork);
		print_it(list, "has taking a fork\n");
		pthread_mutex_lock(&((t_philo *)list)->next->fork);
		print_it(list, "has taking a fork\n");
		print_it(list, "is eating\n");
		ft_usleep(((t_philo *)list)->t_to_eat);
		((t_philo *)list)->eat_counter++;
		pthread_mutex_unlock(&((t_philo *)list)->next->fork);
		pthread_mutex_unlock(&((t_philo *)list)->fork);
		if (((t_philo *)list)->eat_counter == ((t_philo *)list)->n_must_eat)
			break;
		print_it(list, "is sleeping\n");
		ft_usleep(((t_philo *)list)->t_to_sleep);
		print_it(list, "is thinking\n");
	}
	return (NULL);
}

bool	philosophers(t_philo **list)
{
	int			index;
	t_philo		*tmp;

	tmp = *list;
	index = 0;
	if (!init_mutexes(*list))
		return (printf("Philo: Failed to create a new mutex.\n"), false);
	while (index < tmp->philo_count)
	{
		if (pthread_create(&tmp->philo, NULL, routine, tmp))
			return (printf("Philo: Failed to create a new thread.\n"), false);
		
		index++;
		tmp = tmp->next;
		usleep(100);
	}
	index = 0;
	tmp = *list;
	while (index < tmp->philo_count)
	{
		pthread_join(tmp->philo, NULL);
		index++;
		tmp = tmp->next;
	}
	return (true);
}
