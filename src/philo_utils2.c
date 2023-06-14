/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:50 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/14 12:23:24 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_msg(char *msg, t_philo *philo)
{
//    int time;

	pthread_mutex_lock(philo->print_lock);
	//printf("entra\n");
//	time = get_time() - philo->st_data->start_time;
	if (!philo->st_data->end /* && !philo->st_data->max_meals */)
	{
		//pthread_mutex_unlock(philo->print_lock);
		printf("%lu philo %d: %s\n", get_time() - philo->start_time/* time */, philo->id, msg);
		//pthread_mutex_lock(philo->print_lock);
	}
	pthread_mutex_unlock(philo->print_lock);
	//printf("sale\n");
	//printf("nº f: %d\n", philo->st_data->end);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}

/* int	ft_isdigit(char *c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	return (0);
} */
