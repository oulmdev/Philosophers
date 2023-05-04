/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:30:12 by moulmoud          #+#    #+#             */
/*   Updated: 2023/05/04 13:46:17 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static bool	is_number(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] > '9' || str[index] < '0')
			return (false);
		index++;
	}
	return (true);
}

static bool	is_valide(char *av[])
{
	int	index;

	index = 1;
	while (av[index])
		if (!is_number(av[index++]))
			return (false);
	if (ft_atoi(av[1]) > 200)
		return (false);
	if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
		return (false);
	return (true);
}

bool	pars(t_philo **list, char *av[], int ac)
{
	int	philo;
	int	index;

	index = 1;
	philo = 1;
	if (!is_valide(av))
		return (printf("Philo: Wrong input.\n"INPERROR), false);
	while (philo <= ft_atoi(av[1]))
	{
		if (lst_addback(list, new_philo(av, philo)) == false)
			return (printf("Philo: malloc() failed.\n"), false);
		philo++;
	}
	return (true);

}
