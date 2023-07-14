/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:50:33 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/21 12:04:57 by crtorres         ###   ########.fr       */
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
	return ((tm.tv_sec * 1000) + (tm.tv_usec / 1000));
}

void	ft_clear_data(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->philo_id)
		free(data->philo_id);
	if (data->forks)
		free(data->forks);
	if (data->lock)
		free(data->lock);
	if (data->print_lock)
		free(data->print_lock);
}

int	ft_usleep(unsigned long time)
{
	unsigned long	reference;

	reference = time + get_time();
	while (get_time() < reference)
		usleep(200);
	return (0);
}

int	ft_atoi(const char *str)
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
		exit_without_free("error in atoi\n");
	return (sign * j);
}
