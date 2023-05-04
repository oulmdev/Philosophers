/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:49 by moulmoud          #+#    #+#             */
/*   Updated: 2023/05/04 20:52:09 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>


# define RED "\033[0;31m"
# define RESET "\033[0m"
# define INPERROR "- Do not test with more than 200 philosophers\n\
- Do not test with time_to_die or time_to_eat or time_to_sleep under 60 ms.\n\
- Test only with numbers.\n"
# define GUIDE "Example: \n./philo [number_of_philos] [time_to_die] \
[time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]"

typedef struct s_philo
{
	int				philo_id;
	int				philo_count;
	long			t_to_die;
	long 			t_to_eat;
	long 			t_to_sleep;
	long 			t_last_eat;
	long 			t_start;
	int				eat_counter;
	int				n_must_eat;
	bool			is_died;
	bool			is_full;
	bool			finished;
	pthread_t		philo;
	pthread_mutex_t	fork;
	pthread_mutex_t	triger;
	struct s_philo	*next;
}t_philo;


t_philo		*new_philo(char *av[], int i);
bool		lst_addback(t_philo **philo, t_philo *new);
bool		pars(t_philo **list, char *av[], int ac);
int			ft_atoi(char *str);
bool		philosophers(t_philo **list);
long 	get_time(void);
#endif
