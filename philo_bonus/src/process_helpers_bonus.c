/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_helpers_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:17:43 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/21 17:04:38 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	my_sleep(int ms)
{
	long	time_stamp;

	time_stamp = get_time();
	while (get_time() - time_stamp < ms)
		usleep(500);
}

void	print_state(t_philo *philo, char *str)
{
	sem_wait(philo->info->print_sem);
	if (str[3] == 'e')
		philo->last_meal = get_time();
	printf("%lu %i %s\n", get_time(), philo->id, str);
	if (str[0] == 'd')
		return ;
	sem_post(philo->info->print_sem);
}

long	get_time(void)
{
	static long		starting_time;
	struct timeval	start_timestamp;
	long			ret;

	if (starting_time)
	{
		gettimeofday(&start_timestamp, NULL);
		ret = start_timestamp.tv_sec * \
		1000 + start_timestamp.tv_usec / 1000;
		ret -= starting_time;
		return (ret);
	}
	else
	{
		gettimeofday(&start_timestamp, NULL);
		starting_time = start_timestamp.tv_sec * \
		1000 + start_timestamp.tv_usec / 1000;
		return (0);
	}
}
