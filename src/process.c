/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto < jofoto@student.hive.fi >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:07:45 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/11 21:19:17 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static pthread_mutex_t	mutex;

void	my_sleep(int ms)
{
	long	time_stamp;

	time_stamp = get_time();
	while (get_time() - time_stamp < ms)
	{
		usleep(500);
	}
}

void	print_state(t_philo *philo, char *str)
{
	//pthread_mutex_lock(&mutex);
	if(EATING)
		philo->last_meal = get_time();
	printf("%lu %i %s\n", get_time(), philo->id, str);
	//pthread_mutex_unlock(&mutex);
}

void	eat(t_philo	*philo)
{
	pthread_mutex_lock(&philo->fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->next->fork);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	usleep(philo->info->ms_to_eat * 1000);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	*routine(void	*data)
{
	t_philo	*self;

	self = (t_philo*)data;
	while(1)
	{
		eat(self);
		print_state(self, "is sleeping");
		usleep(self->info->ms_to_sleep * 1000);
		print_state(self, "is thinking");
	}
}

int	philo_alive(t_philo *philo)
{
	//printf("%i\n", philo->info->ms_to_die - (get_time() - philo->last_meal));
	return(philo->info->ms_to_die - (get_time() - philo->last_meal));
}

void	start_process(t_philo *head, t_info info)
{
	int	i;

	i = 0;
	get_time();
	pthread_mutex_init(&mutex, NULL);
	while(i < info.philos_amount)
	{
		pthread_create(&head->thread, NULL, &routine, head);
		pthread_detach(head->thread);
		head = head->next;
		i++;
		usleep(50);
	}
	while(philo_alive(head))
		head = head->next;
	print_state(head, "died\n");
}