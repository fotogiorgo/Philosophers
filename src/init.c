/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:12:05 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/12 18:02:58 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_philo(t_philo	**head, t_info *info)
{
	int	i;
	t_philo	*node;

	i = 0;
	while (i < info->philos_amount)
	{
		node = malloc(sizeof(t_philo));
		if (node == NULL)
			return (0);
			//return (destroy_philo(head));
		node->id = i+1;
		node->stop = 0;
		node->last_meal = 0;
		if (pthread_mutex_init(&node->fork, NULL) != 0) //remember to destroy in destoy_philo
			return (0);
			//return (destroy_philo(head));
		node->info = info;
		ft_lstadd_back(head, node);
		i++;
	}
	ft_lstlast(*head)->next = *head;
	return (1);
}

int	get_info(t_info *info, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (0);
	info->philos_amount = ft_atoi(argv[1]);
	info->ms_to_die = ft_atoi(argv[2]);
	info->ms_to_eat = ft_atoi(argv[3]);
	info->ms_to_sleep = ft_atoi(argv[4]);
	if(argc == 6)
		info->times_to_eat = ft_atoi(argv[5]);
	else
		info->times_to_eat = -1;
	return (1);
}
