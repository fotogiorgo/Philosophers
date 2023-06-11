/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto < jofoto@student.hive.fi >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:52:08 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/11 18:38:42 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*head;

	head = 0;
	if (!get_info(&info, argc, argv))
		return (0);
	if (!init_philo(&head, &info))
		return (1);
	start_process(head, info);
	//destroy_info(info);
	//destroy_philo(&head); // make it return 0 on success
}