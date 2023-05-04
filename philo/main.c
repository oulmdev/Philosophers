/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:00:12 by moulmoud          #+#    #+#             */
/*   Updated: 2023/05/04 20:53:52 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int main(int ac, char *av[])
{
	t_philo *list;

	list = NULL;

	if (ac < 5 || ac > 6)
		return (printf("Philo: Wrong number of argumment.\n"GUIDE), 1);
	if (pars(&list, av, ac) == false)
		return (false);
	if (philosophers(&list) == false)
		return (false);
}
