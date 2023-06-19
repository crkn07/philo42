/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:50 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/19 18:05:11 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_msg(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
//	time = get_time() - philo->st_data->start_time;
	if (philo->st_data->end != 1)
		printf("%lu philo %d: %s\n", get_time() - philo->start_time/* time */, philo->id, msg);
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

/* int	ft_isdigit(char *c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	return (0);
} */
