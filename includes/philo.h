/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:10:04 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/12 18:49:05 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# define EATING (str[3] == 'e')
# define PHILO_ALIVE (head->info->ms_to_die - (get_time() - head->last_meal))

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
	int					stop;
	long				last_meal;
	pthread_t			thread;
	pthread_mutex_t		fork;
	t_info				*info;
	struct s_philo		*next;
}				t_philo;

//process
void	start_process(t_philo *head, t_info info);
long	get_time();


//helpers
int		ft_atoi(const char *str);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lstlast(t_philo *lst);

//init
int	get_info(t_info *info, int argc, char **argv);
int	init_philo(t_philo	**head, t_info *info);

#endif