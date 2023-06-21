/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:07:45 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/21 17:27:19 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	my_sleep(int ms)
{
	long	time_stamp;

	time_stamp = get_time();
	while (get_time() - time_stamp < ms)
		usleep(500);
}

void	print_state(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	if (str[3] == 'e')
		philo->last_meal = get_time();
	printf("%lu %i %s\n", get_time(), philo->id, str);
	if (str[0] == 'd')
		return ;
	pthread_mutex_unlock(&philo->info->print_mutex);
}

int	philo_alive_and_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->philos_amount_mutex);
	if (((philo->info->ms_to_die - (get_time() - philo->last_meal) < 0)
			&& philo->id) || philo->info->philos_amount == 0)
		return (0);
	pthread_mutex_unlock(&philo->info->philos_amount_mutex);
	return (1);
}

int	philo_alive(t_philo *philo)
{
	if ((philo->info->ms_to_die - (get_time() - philo->last_meal) >= 0))
		return (1);
	return (0);
}

void	start_process(t_philo *philo, t_info info)
{
	int		i;
	void	*(*func_ptr[2])(void *);
	int		(*check_state)(t_philo *philo);

	func_ptr[0] = &even_philo;
	func_ptr[1] = &odd_philo;
	if (info.times_to_eat > 0)
		check_state = &philo_alive_and_eaten;
	else
		check_state = &philo_alive;
	i = 0;
	get_time();
	while (i < info.philos_amount)
	{
		if (pthread_create(&philo->thread, NULL, \
			func_ptr[philo->id % 2], philo) != 0)
			return ;
		pthread_detach(philo->thread);
		philo = philo->next;
		i++;
	}
	while (check_state(philo))
		philo = philo->next;
	if (philo->info->philos_amount)
		print_state(philo, "died");
}
