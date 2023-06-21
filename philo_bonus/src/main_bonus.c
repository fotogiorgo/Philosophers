/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:52:08 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/21 17:20:04 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	start_process(t_philo *philo, t_info info)
{
	void	(*func_ptr[2])(t_philo *);
	int		i;

	func_ptr[0] = &even_philo;
	func_ptr[1] = &odd_philo;
	i = 0;
	get_time();
	while (i < info.philos_amount)
	{
		if (fork_wrapper(&(philo->pid)) == 0)
			func_ptr[philo->id % 2](philo);
		else
		{
			philo = philo->next;
			i++;
		}
	}
}

void	*wait_eaten(void *data)
{
	sem_t	*death_sem;

	death_sem = (sem_t *)data;
	while (wait(NULL) > 0)
		;
	sem_post(death_sem);
	return (NULL);
}

int	start_eaten_check(sem_t	*sem)
{
	pthread_t	eaten;

	if (pthread_create(&eaten, NULL, wait_eaten, sem) != 0)
		return (0);
	pthread_detach(eaten);
	return (1);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_philo		*philo;
	void		*(*func_ptr[2])(void *);

	philo = NULL;
	if (!get_info(&info, argc, argv))
		return (1);
	if (!init_semaphores(&info))
		return (2);
	if (!init_philo(&philo, &info))
	{
		destroy_semaphores();
		return (3);
	}
	start_process(philo, info);
	if (start_eaten_check(info.death_sem))
		sem_wait(info.death_sem);
	kill_processes(philo);
	destroy_semaphores();
	destroy_philo(&philo);
}
