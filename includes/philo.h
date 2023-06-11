/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto < jofoto@student.hive.fi >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:10:04 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/11 13:51:59 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#ifdef PHILO_H
//# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct	s_info
{
	int	ms_to_eat;
	int	ms_to_die;
	int	ms_to_sleep;
	int	times_to_eat;
	int	philos_amount;
}				t_info;


typedef struct	s_philo
{
	int					id;
	long				last_meal;
	pthread_t			thread;
	pthread_mutex_t		fork;
	t_info				*info;
	struct philo		*next;
}				t_philo;



//#endif