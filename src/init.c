/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:28:31 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/06 19:26:29 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_init_data(t_data *data, int argc, char **argv)
{
	data->nbr_philo = (unsigned long)ft_atoi(argv[1], data);
	data->death_time = (unsigned long)ft_atoi(argv[2], data);
	data->philos = malloc(sizeof(t_philo) * data->nbr_philo);
	if (!data->philos)
		exit_error("failed to alloc memory philosopher\n", data);
	data->eat_time = (unsigned long)ft_atoi(argv[3], data);
	data->sleep_time = (unsigned long)ft_atoi(argv[4], data);
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
	//printf("nº filo: %d\n", data->nbr_philo);
	return (0);
}

/**
 * The function initializes mutexes for forks, meals, and writing in a dining
 * philosophers problem.
 * 
 * @param data The parameter "data" is a pointer to a struct of type "t_data". This
 * struct likely contains information about the simulation being run, such as the
 * number of philosophers, the time they can spend eating, and the number of meals
 * they must eat before the simulation ends. The function initializes mutexes
 * 
 * @return The function `ft_init_mutex` is returning an integer value of 0.
 */
int	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			exit_error("failed init mutex\n", data);
		i++;
	}
	if (pthread_mutex_init(&(data->meals), NULL))
		exit_error("failed init mutex\n", data);
	if (pthread_mutex_init(&(data->write), NULL))
		exit_error("failed init mutex\n", data);
	return (0);
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
	return (1);
}
