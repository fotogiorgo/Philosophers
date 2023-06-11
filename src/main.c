/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto < jofoto@student.hive.fi >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:52:08 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/11 13:58:26 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

long	get_time()
{
	static long		starting_time;
	struct timeval	start_timestamp;
	long			ret;

	if(starting_time)
	{
		gettimeofday(&start_timestamp, NULL);
		ret = start_timestamp.tv_sec * 1000 + start_timestamp.tv_usec/1000;
		ret -= starting_time;
		return (ret);
	}
	else
	{
		gettimeofday(&start_timestamp, NULL);
		starting_time = start_timestamp.tv_sec * 1000 + start_timestamp.tv_usec/1000;
		return (0);
	}
}

int	main()
{
	t_info	*info;
	t_philo	*head;

	init_info(info);
	init_philo(&head, info);
	start_process(head);
	destroy_info(info);
	destroy_philo(&head);
}