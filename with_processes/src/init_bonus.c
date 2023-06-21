/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:12:05 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/21 19:41:08 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	validate_input(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Wrong input!\n\
number_of_philosophers, time_to_die, time_to_eat, time_to_sleep\n\
optional: [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	if (ft_atoi(argv[1]) > MAX_PHILOS)
	{
		printf("Max allowed philosophers: 200\n");
		return (0);
	}
	while (argc > 1)
	{
		argc--;
		if (ft_atoi(argv[argc]) < 0)
		{
			printf("No negatives allowed!\n");
			return (0);
		}
	}
	return (1);
}

int	init_semaphores(t_info *info)
{
	destroy_semaphores();
	info->forks = sem_open(FORK_SEM, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, \
							info->philos_amount);
	info->even_eat = sem_open(EVEN_EAT_SEM, O_CREAT | O_EXCL, \
							S_IRUSR | S_IWUSR, 0);
	info->print_sem = sem_open(PRINT_SEM, O_CREAT | O_EXCL, \
							S_IRUSR | S_IWUSR, 1);
	info->stop_sem = sem_open(DEATH_SEM, O_CREAT | O_EXCL, \
							S_IRUSR | S_IWUSR, 0);
	if (info->forks == SEM_FAILED || \
		info->even_eat == SEM_FAILED || info->print_sem == SEM_FAILED)
	{
		destroy_semaphores();
		printf("semaphores failed\n");
		return (0);
	}
	return (1);
}

int	get_info(t_info *info, int argc, char **argv)
{
	if (!validate_input(argc, argv))
		return (0);
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

int	init_philo(t_philo	**head, t_info *info)
{
	int		i;
	t_philo	*node;

	i = 0;
	if (info->philos_amount < 1)
		return (0);
	while (i < info->philos_amount)
	{
		node = (t_philo *)malloc(sizeof(t_philo));
		if (node == NULL)
			return (destroy_philo(head));
		node->id = i + 1;
		node->last_meal = 0;
		node->next = NULL;
		node->info = info;
		ft_lstadd_back(head, node);
		i++;
	}
	ft_lstlast(*head)->next = *head;
	return (1);
}
