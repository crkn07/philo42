/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:50:33 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/09 17:30:23 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	exit_error(char *msg, t_data *data)
{
	ft_putstr_fd(msg, 2);
	if (data)
		ft_clear_data(data);
	exit (EXIT_FAILURE);
}

unsigned long	get_time(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return ((tm.tv_sec * (unsigned long)1000) + (tm.tv_usec / 1000));
}

void	ft_clear_data(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->lock)
		free(data->lock);
	if (data->print_lock)
		free(data->print_lock);
}

int	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_time();
	while ((get_time() - start) <= time)
		usleep(time/10);
	return (0);
}

int	ft_atoi(const char *str, t_data *data)
{
	int			sign;
	int			i;
	long int	j;

	i = 0;
	j = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i])
	{
		j = (j * 10) + (str[i] - '0');
		i++;
	}
	if ((sign * j) > 2147483647 || (sign * j) < -2147483648)
		exit_error("error\n", data);
	return (sign * j);
}