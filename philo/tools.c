/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:31:27 by moulmoud          #+#    #+#             */
/*   Updated: 2023/05/04 16:46:30 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	ft_atoi(char *str)
{
	int	index;
	int	number;

	index = 0;
	number = 0;
	while (str[index] == ' ' || str[index] == '\t' || str[index] == '\n'
		|| str[index] == '\v' || str[index] == '\f' || str[index] == '\r')
		index++;
	if (str[index] == '+')
		index++;
	while (str[index])
	{
		if (str[index] < '0' || str[index] > '9')
			break ;
		number = number * 10 + (str[index] - '0');
		index++;
	}
	return (number);
}

t_philo	*new_philo(char *av[], int i)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->philo_id = i;
	new->philo_count = ft_atoi(av[1]);
	new->t_to_die = ft_atoi(av[2]);
	new->t_to_eat = ft_atoi(av[3]);
	new->t_to_sleep = ft_atoi(av[4]);
	if (av[5])
		new->n_must_eat = ft_atoi(av[5]);
	else
		new->n_must_eat = -1;
	new->is_die = false;
	new->is_full = false;
	new->finished = false;
	new->eat_counter = 0;
	new->next = NULL;
	return (new);
}

bool	lst_addback(t_philo **philo, t_philo *new)
{
	t_philo	*last;

	if (!new)
		return (false);
	if (!*philo)
	{
		*philo = new;
		new->next = (*philo);
		return (true);
	}
	last = *philo;
	while (last->next != (*philo))
		last = last->next;
	last->next = new;
	new->next = *philo;
	return (true);
}
