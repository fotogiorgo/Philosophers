/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:52:08 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/21 18:46:57 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*head;

	head = NULL;
	if (!init_info(&info, argc, argv))
		return (1);
	if (!init_philo(&head, &info))
	{
		destroy_info(&info);
		return (2);
	}
	start_process(head, info);
	//printf("\033[31mending.......\n");
	head->id = 1;
	destroy_philo(&(head), info);
	destroy_info(&info);
	return (0);
}
