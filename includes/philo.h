/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:10:04 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/15 14:22:41 by jofoto           ###   ########.fr       */
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

typedef struct s_info
{
	int					ms_to_eat;
	int					ms_to_die;
	int					ms_to_sleep;
	int					times_to_eat;
	int					philos_amount;
	pthread_mutex_t		philos_amount_mutex;
	pthread_mutex_t		print_mutex;
}				t_info;

typedef struct s_philo
{
	int					id;
	long				last_meal;
	pthread_t			thread;
	pthread_mutex_t		fork;
	t_info				*info;
	struct s_philo		*next;
}				t_philo;

//process
void	start_process(t_philo *head, t_info info);
void	*odd_philo(void *data);
void	*even_philo(void *data);
long	get_time(void);
void	print_state(t_philo *philo, char *str);
void	my_sleep(int ms);

//helpers
int		ft_atoi(const char *str);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lstlast(t_philo *lst);

//init
int		init_info(t_info *info, int argc, char **argv);
int		init_philo(t_philo	**head, t_info *info);
int		destroy_philo(t_philo	**head, t_info info);
void	destroy_info(t_info *info);

#endif