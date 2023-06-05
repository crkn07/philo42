/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:28:31 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/05 17:20:26 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_init_data(t_data *data, int argc, char **argv)
{
	data->nbr_philo = (unsigned long)argv[1];
	data->death_time = (unsigned long)argv[2];
	data->philos = malloc(sizeof(t_philo) * data->nbr_philo);
	if (!data->philos)
		exit_error("failed to alloc memory philosopher\n", data);
	data->eat_time = (unsigned long)argv[3];
	data->sleep_time = (unsigned long)argv[4];
	data->max_meals = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	if (!data->forks)
		exit_error("failed to alloc memory forks\n", data);
	if (argc == 6)
		data->nbr_meals = ft_atoi(argv[5], data);
	else
		data->nbr_meals = 0;
	if (data->nbr_philo <= 0 || data->nbr_philo > 200 || data->death_time < 0
		|| data->eat_time < 0 || data->sleep_time < 0)
		exit_error("invalid input data\n", data);
}

int	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL));
			return (0);
		i++;
	}
	if (pthread_mutex_init(&(data->meals), NULL));
		return (0);
	if (pthread_mutex_init(&(data->write), NULL));
		return (0);
	return (1);
}

int	ft_create_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		data->philos[i].n_meals = 0;
		data->philos[i].st_data = data;
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = i + 1 % (data->nbr_philo);
		i++;	
	}
}
