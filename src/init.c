/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:12:05 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/15 14:25:00 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy_info(t_info *info)
{
	pthread_mutex_destroy(&(info->philos_amount_mutex));
	pthread_mutex_destroy(&(info->print_mutex));
}

int	destroy_philo(t_philo	**head, t_info info)
{
	if (*head == NULL)
		return (0);
	if ((*head)->next && (*head)->next->id != 1)
		destroy_philo(&((*head)->next), info);
	pthread_mutex_destroy(&((*head)->fork));
	free(*head);
	return (0);
}

int	init_philo(t_philo	**head, t_info *info)
{
	int		i;
	t_philo	*node;

	i = 0;
	if (info->philos_amount < 1)
		return (0);
	while (i < info->philos_amount)
	{
		node = malloc(sizeof(t_philo));
		if (node == NULL)
			return (destroy_philo(head, *info));
		node->id = i + 1;
		node->last_meal = 0;
		node->next = NULL;
		if (pthread_mutex_init(&node->fork, NULL) != 0)
			return (destroy_philo(head, *info));
		node->info = info;
		ft_lstadd_back(head, node);
		i++;
	}
	ft_lstlast(*head)->next = *head;
	return (1);
}

int	validate_input(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Wrong input!\n\
number_of_philosophers, time_to_die, time_to_eat, time_to_sleep\n\
optional: [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	return (1);
}

int	init_info(t_info *info, int argc, char **argv)
{
	if (!validate_input(argc, argv))
		return (0);
	if (pthread_mutex_init(&info->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&info->philos_amount_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&(info->print_mutex));
		return (0);
	}
	info->philos_amount = ft_atoi(argv[1]);
	info->ms_to_die = ft_atoi(argv[2]);
	info->ms_to_eat = ft_atoi(argv[3]);
	info->ms_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->times_to_eat = ft_atoi(argv[5]);
	else
		info->times_to_eat = -1;
	return (1);
}
