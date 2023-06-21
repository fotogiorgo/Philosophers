/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:51:36 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/21 17:01:26 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	kill_processes(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->philos_amount)
	{
		kill(philo->pid, SIGKILL);
		philo = philo->next;
		i++;
	}
}

void	destroy_semaphores(void)
{
	sem_unlink(FORK_SEM);
	sem_unlink(PRINT_SEM);
	sem_unlink(EVEN_EAT_SEM);
	sem_unlink(DEATH_SEM);
}

int	destroy_philo(t_philo	**head)
{
	if (*head == NULL)
		return (0);
	if ((*head)->next && (*head)->next->id != 1)
		destroy_philo(&((*head)->next));
	free(*head);
	return (0);
}
