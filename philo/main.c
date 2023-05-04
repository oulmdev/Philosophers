/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:00:12 by moulmoud          #+#    #+#             */
/*   Updated: 2023/05/04 15:32:34 by moulmoud         ###   ########.fr       */
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

	//t_philo *tmp;

	//tmp = list;
	//while (tmp)
	//{
	//	printf("------------------------------\n");
	//	printf("philo id = %d\n", tmp->philo_id);
	//	printf("philo t_to_die = %lld\n", tmp->t_to_die);
	//	printf("philo t_to_eat = %lld\n", tmp->t_to_eat);
	//	printf("philo t_to_sleep = %lld\n", tmp->t_to_sleep);
	//	printf("philo n_must_eat = %d\n", tmp->n_must_eat);
	//	printf("philo philo_count = %d\n", tmp->philo_count);
	//	printf("------------------------------\n");
	//	tmp = tmp->next;
	//	if (tmp == list)
	//		break ;
	//}
}
