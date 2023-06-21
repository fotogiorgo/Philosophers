/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:10:04 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/21 19:41:08 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# define MAX_PHILOS 200
# define FORK_SEM "fork_sem"
# define EVEN_EAT_SEM "even_eat"
# define PRINT_SEM "print_sem"
# define DEATH_SEM "stop_sem"

typedef struct s_info
{
	int					ms_to_eat;
	int					ms_to_die;
	int					ms_to_sleep;
	int					times_to_eat;
	int					philos_amount;
	sem_t				*print_sem;
	sem_t				*stop_sem;
	sem_t				*forks;
	sem_t				*even_eat;
}				t_info;

typedef struct s_philo
{
	int					id;
	long				last_meal;
	int					pid;
	pthread_t			thread;
	t_info				*info;
	struct s_philo		*next;
}				t_philo;

//PROCESS
void	odd_philo(t_philo *self);
void	even_philo(t_philo *self);
long	get_time(void);
void	print_state(t_philo *philo, char *str);
void	my_sleep(int ms);

//HELPERS
int		ft_atoi(const char *str);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lstlast(t_philo *lst);
int		fork_wrapper(int *ret);

//INIT
int		get_info(t_info *info, int argc, char **argv);
int		init_philo(t_philo	**head, t_info *info);
int		init_semaphores(t_info *info);

//DESTROY
void	destroy_semaphores(void);
int		destroy_philo(t_philo	**head);
void	kill_processes(t_philo *philo);

#endif