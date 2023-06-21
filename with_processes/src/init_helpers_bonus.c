/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:28:09 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/21 12:59:27 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	fork_wrapper(int *ret)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		write(2, "fork error\n", 12);
		exit(1);
	}
	if (ret != NULL && pid != 0)
		*ret = pid;
	return (pid);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	if (lst == NULL)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	if (lst == 0)
		return ;
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	else
		ft_lstlast(*lst)->next = new;
}

static int	positive_num(char *str)
{
	int			result;
	long long	rslt;

	rslt = 0;
	result = 0;
	while (48 <= *str && *str <= 57)
	{
		result *= 10;
		result += *str - 48;
		rslt *= 10;
		rslt += *str -48;
		str++;
		if (rslt < 0)
		{
			return (-1);
		}
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
	{
		str++;
	}
	if (*str == '-')
		return (-1);
	else if (*str == '+')
	{
		str++;
		return (positive_num((char *)str));
	}
	else
		return (positive_num((char *)str));
}
