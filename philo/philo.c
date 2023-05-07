/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:32:12 by moulmoud          #+#    #+#             */
/*   Updated: 2023/05/07 16:56:27 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "philo.h"

bool	init_monitor(t_monitor **monitor, char *av[]);
bool	init_philos(t_philo **philos, t_monitor **monitor);
bool	start_simulation(t_philo *philos);

int	main(int ac, char *av[])
{
	t_monitor		*monitor;
	t_philo			*philos;

	philos = NULL;
	if (ac < 5 || ac > 6)
		return (printf("Error: Wrong number of arguments\n"));
	if (parsing(ac, av))
		return (printf("Error: Wrong arguments\n"));
	if (init_monitor(&monitor, av) == false)
		return (printf("Error: Monitor initialization failed\n"));
	if (!init_philos(&philos, &monitor))
		return (printf("Error: Philos initialization failed\n"));
	if (!start_simulation(philos))
		return (printf("Error: Simulation failed\n"));
	return (0);
}

bool	init_monitor(t_monitor **monitor, char *av[])
{
	*monitor = malloc(sizeof(t_monitor));
	if (!*monitor)
		return (false);
	(*monitor)->nb_philos = ft_atoi(av[1]);
	(*monitor)->time_to_die = ft_atoi(av[2]);
	(*monitor)->time_to_eat = ft_atoi(av[3]);
	(*monitor)->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		(*monitor)->nb_eat = ft_atoi(av[5]);
	else
		(*monitor)->nb_eat = -1;
	(*monitor)->is_dead = false;
	(*monitor)->start_time = get_time();
	if (pthread_mutex_init(&((*monitor)->print), NULL))
		return (false);
	if (pthread_mutex_init(&((*monitor)->dead), NULL))
		return (false);
	if (pthread_mutex_init(&((*monitor)->eating), NULL))
		return (false);
	return (true);
}

bool	init_philos(t_philo **philo, t_monitor **monitor)
{
	int	id;
	int	number_of_philos;

	number_of_philos = (*monitor)->nb_philos;
	id = 1;
	while (number_of_philos--)
	{
		if (lst_addback(philo, newphilo(id, monitor)))
			return (false);
		id++;
	}
	return (true);
}
