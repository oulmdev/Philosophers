/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:25:09 by moulmoud          #+#    #+#             */
/*   Updated: 2023/05/06 18:51:52 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H



# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_monitor{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	bool			is_dead;
	long			start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	eating;
}t_monitor;

typedef struct s_philo{
	int				id;
	long			last_eat;
	int				eat_count;
	pthread_mutex_t	last_eat_mutex;
	bool			is_full;
	t_monitor		*monitor;
	pthread_t		thread;
	pthread_mutex_t	fork;
	struct s_philo	*next;
}t_philo;

int			parsing(int ac, char *av[]);
int			ft_atoi(char *str);
long		get_time(void);
t_philo		*newphilo(int id, t_monitor **monitor);
int			lst_addback(t_philo **philo, t_philo *new);
bool		start_simulation(t_philo *philos);

#endif
