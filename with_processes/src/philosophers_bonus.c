/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:17:06 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/21 19:41:08 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	eat(t_philo	*philo)
{
	sem_wait(philo->info->forks);
	print_state(philo, "has taken a fork");
	sem_wait(philo->info->forks);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	my_sleep(philo->info->ms_to_eat);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

static void	*death_monitoring(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while ((philo->info->ms_to_die - (get_time() - philo->last_meal) >= 0))
		usleep(1000);
	print_state(philo, "died");
	sem_post(philo->info->stop_sem);
	return (NULL);
}

void	odd_philo(t_philo *self)
{
	int		count_meals_bool;
	int		meals;
	int		ms_to_sleep;
	sem_t	*even_eat;

	even_eat = self->info->even_eat;
	count_meals_bool = (self->info->times_to_eat > 0);
	meals = self->info->times_to_eat;
	ms_to_sleep = self->info->ms_to_sleep;
	if (pthread_create(&self->thread, NULL, death_monitoring, self) != 0)
	{
		sem_post(self->info->stop_sem);
		exit(0);
	}
	pthread_detach(self->thread);
	while (meals != 0)
	{
		eat(self);
		sem_post(even_eat);
		meals -= count_meals_bool;
		print_state(self, "is sleeping");
		my_sleep(ms_to_sleep);
		print_state(self, "is thinking");
	}
	exit(1);
}

void	even_philo(t_philo *self)
{
	int		count_meals_bool;
	int		meals;
	int		ms_to_sleep;
	sem_t	*even_eat;

	even_eat = self->info->even_eat;
	count_meals_bool = (self->info->times_to_eat > 0);
	meals = self->info->times_to_eat;
	ms_to_sleep = self->info->ms_to_sleep;
	if (pthread_create(&self->thread, NULL, death_monitoring, self) != 0)
	{
		sem_post(self->info->stop_sem);
		exit(0);
	}
	pthread_detach(self->thread);
	while (meals != 0)
	{
		sem_wait(even_eat);
		eat(self);
		meals -= count_meals_bool;
		print_state(self, "is sleeping");
		my_sleep(ms_to_sleep);
		print_state(self, "is thinking");
	}
	exit(1);
}
