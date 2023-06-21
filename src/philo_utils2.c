/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:50 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/21 13:11:57 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_msg(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	if (*(philo->end) == 0)
	{
		if (philo->id % 5 == 0)
			printf(ORANGE"%lums philo %d: %s\n"RESET,
				get_time() - philo->start_time, philo->id, msg);
		else if (philo->id % 5 == 1)
			printf(BLUE"%lums philo %d: %s\n"RESET,
				get_time() - philo->start_time, philo->id, msg);
		else if (philo->id % 5 == 2)
			printf(YELLOW"%lums philo %d: %s\n"RESET,
				get_time() - philo->start_time, philo->id, msg);
		else if (philo->id % 5 == 3)
			printf(ROSE"%lums philo %d: %s\n"RESET,
				get_time() - philo->start_time, philo->id, msg);
		else if (philo->id % 5 == 4)
			printf(LGREEN"%lums philo %d: %s\n"RESET,
				get_time() - philo->start_time, philo->id, msg);
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
			write(fd, &s[i], sizeof(char));
	}
}

void	exit_without_free(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}
