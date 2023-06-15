/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   odd_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:18:37 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/15 14:27:31 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	odd_eat(t_philo	*philo)
{
	pthread_mutex_lock(&philo->next->fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->fork);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	my_sleep(philo->info->ms_to_eat);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	*odd_philo(void	*data)
{
	t_philo	*self;
	int		count_meals_bool;
	int		meals;
	int		ms_to_sleep;

	self = (t_philo *)data;
	count_meals_bool = (self->info->times_to_eat > 0);
	meals = self->info->times_to_eat;
	ms_to_sleep = self->info->ms_to_sleep;
	while (meals != 0)
	{
		odd_eat(self);
		meals -= count_meals_bool;
		print_state(self, "is sleeping");
		my_sleep(ms_to_sleep);
		print_state(self, "is thinking");
	}
	self->id = 0;
	pthread_mutex_lock(&self->info->philos_amount_mutex);
	self->info->philos_amount--;
	pthread_mutex_unlock(&self->info->philos_amount_mutex);
	return (NULL);
}
