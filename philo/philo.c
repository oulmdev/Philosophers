/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:53:13 by moulmoud          #+#    #+#             */
/*   Updated: 2023/05/05 19:57:28 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	set_end(t_philo *list);

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

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
	if (philo->finished == true || philo->is_died == true)
		return ;
	while (tmp->philo_id != 1)
		tmp = tmp->next;
	if (philo->finished == true || philo->is_died == true)
	{
		pthread_mutex_unlock(&tmp->triger);
		return ;
	}
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
		print_it(list, "has taken a fork\n");
		if (((t_philo *)list)->one_philo == true)
			return (ft_usleep(((t_philo *)list)->t_to_die),
				print_it(list, "died\n"), NULL);
		pthread_mutex_lock(&((t_philo *)list)->next->fork);
		print_it(list, "has taken a fork\n");
		print_it(list, "is eating\n");
		((t_philo *)list)->t_last_eat
			= get_time () - ((t_philo *)list)->t_start;
		ft_usleep(((t_philo *)list)->t_to_eat);
		((t_philo *)list)->eat_counter++;
		pthread_mutex_unlock(&((t_philo *)list)->next->fork);
		pthread_mutex_unlock(&((t_philo *)list)->fork);
		if (((t_philo *)list)->eat_counter == ((t_philo *)list)->n_must_eat)
			break ;
		print_it(list, "is sleeping\n");
		ft_usleep(((t_philo *)list)->t_to_sleep);
		print_it(list, "is thinking\n");
	}
	return (NULL);
}

void	set_end(t_philo *list)
{
	int	index;

	index = 1;
	while (index <= list->philo_count)
	{
		list->is_died = true;
		list->finished = true;
		list = list->next;
		index++;
	}
}

void *is_died(void *list)
{
	t_philo	*tmp;
	int		index;

	tmp = (t_philo *)list;
	while (tmp->finished == false)
	{
		if ((get_time() - tmp->t_start) - tmp->t_last_eat
			> tmp->t_to_die && tmp->finished == false)
		{
			print_it(tmp, "died\n");
			set_end(list);
			return (list);
		}
		usleep(100);
		index++;
		tmp = tmp->next;
	}
	return (list);
}

bool	philosophers(t_philo **list)
{
	int			index;
	t_philo		*tmp;
	pthread_t	dead_check;

	tmp = *list;
	index = 0;
	if (!init_mutexes(*list))
		return (printf("Philo: Failed to create a new mutex.\n"), false);
	while (index < tmp->philo_count)
	{
		if (pthread_create(&tmp->philo, NULL, routine, tmp))
			return (printf("Philo: Failed to create a new thread.\n"), false);
		if (pthread_create(&dead_check, NULL, is_died, tmp))
			return (printf("Philo: Failed to create a new thread.\n"), false);
		pthread_detach(dead_check);
		usleep(100);
		tmp = tmp->next;
		index++;
	}
	index = 0;
	tmp = (*list);
	while (index < tmp->philo_count)
	{
		pthread_join(tmp->philo, NULL);
		index++;
		tmp = tmp->next;
	}
	return (true);
}
