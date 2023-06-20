/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:50 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/20 17:08:14 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_msg(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	if (philo->st_data->end != 1)
	{
		if (philo->id % 5 == 0)
			printf(ORANGE"%lu philo %d: %s\n"RESET, get_time() - philo->start_time, philo->id, msg);
		else if (philo->id % 5 == 1)	
			printf(BLUE"%lu philo %d: %s\n"RESET, get_time() - philo->start_time, philo->id, msg);
		else if (philo->id % 5 == 2)
			printf(YELLOW"%lu philo %d: %s\n"RESET, get_time() - philo->start_time, philo->id, msg);
		else if (philo->id % 5 == 3)
			printf(ROSE"%lu philo %d: %s\n"RESET, get_time() - philo->start_time, philo->id, msg);
		else if (philo->id % 5 == 4)		
			printf(LGREEN"%lu philo %d: %s\n"RESET, get_time() - philo->start_time, philo->id, msg);
	}
	pthread_mutex_unlock(philo->print_lock);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	if (s)
	{
		while (s[++i])
			write(fd, &s, sizeof(char));
	}
}
