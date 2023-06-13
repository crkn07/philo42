/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:56:18 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/12 23:17:42 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_init(t_data *data, char **argv)
{
	ft_init_data(data, argv);
	//ft_init_mutex(data);
	return (0);
}

int	ft_create_threads(t_data *data, int argc, char **argv)
{
	int	i;

	i = -1;
	//data->start_time = get_time();
	pthread_mutex_lock(data->print_lock);
	while(++i < data->nbr_philo)
	{
		if (!ft_create_philo(data, argc, argv))
			exit_error("failed create philos\n", data);
		data->philos[i].last_meal = get_time();
		pthread_create(&data->philo_id[i], NULL, routine,
			&(data->philos[i]));
		printf("entra create_threads\n");
			//exit_error("a problem has ocurred creating threads", data);
	}
	pthread_mutex_unlock(data->print_lock);
/* 	while (stop == 1)
	{
		i = -1;
		while ( ++i < data->nbr_philo)
		{
			pthread_mutex_lock(data->print_lock);
			if (!check_death(data, &data->philos[i]))
			{	stop = 0;
				continue ;
			}
			pthread_mutex_unlock(data->print_lock);
		}
	} */
	//pthread_mutex_unlock(&data->write);
	return (0);
}

void	end_subprocesses(t_data *data)
{
	int	i;

	i = -1;
	while (1)
	{
		i = -1;
		while ( ++i < data->nbr_philo)
		{
			pthread_mutex_lock(data->philos[i].lock);
			if (!check_death(data, &data->philos[i]))
				return ;
			pthread_mutex_unlock(data->philos[i].lock);
		}
	}
}
/* int	ft_check_args(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (argc < 5 || argc > 6)
		exit_error("invalid number of arguments\n", data);
	// printf("argc: %d\n", argc);
	while (i < argc)
	{
		// printf("entra\n");
		printf("argv[j]: %s\n", argv[j]);

		if (!ft_isdigit(argv[i]))
			exit_error("invalid type of argument\n", data);
		i++;
	}
	// printf("atoi: %s\n", argv[j]);
	return (0);
} */
/* void	ft_leaks()
{
	system("leaks -q philo");
} */
int	main(int argc, char **argv)
{
	t_data	data;

	//atexit(ft_leaks);
	data.end = 0;
	if (argc < 5 || argc > 6)
		exit_error("invalid number of arguments\n", &data);
	//ft_check_args(argc, argv, &data);
	ft_init(&data, argv);
	ft_create_threads(&data, argc, argv);
	printf("entra\n");
	end_subprocesses(&data);
	end_philos(&data);
	return (0);
}