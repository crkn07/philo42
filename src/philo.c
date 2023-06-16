/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:56:18 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/16 15:12:00 by crtorres         ###   ########.fr       */
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
		if (!ft_create_philo(data, argc, argv, i))
			exit_error("failed create philos\n", data);
		//data->philos[i].last_meal = get_time();
		pthread_create(&data->philo_id[i], NULL, routine, &(data->philos[i]));
	}
	pthread_mutex_unlock(data->print_lock);
	return (0);
}

void	end_subprocesses(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while ( ++i < data->nbr_philo)
		{
			pthread_mutex_lock(data->philos[i].lock);
			if (!check_death(data, i))
				return ;
			pthread_mutex_unlock(data->philos[i].lock);
		}
	}
}
int	ft_check_args(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (++j < argc)
	{
		i = -1;
		while (argv[j][++i])
		{
			if (argv[j][i] < 48 || argv[j][i] > 57)
				exit_error("invalid type of argument\n", data);
		}
	}
	if (!ft_atoi(argv[2], data) || !ft_atoi(argv[3], data) || !ft_atoi(argv[4], data))
		exit_error("invalid number of arguments\n", data);
	if (argc == 6)
		if (!ft_atoi(argv[5], data))
			exit_error("invalid number of arguments\n", data);
	return (0);
}
/* void	ft_leaks()
{
	system("leaks -q philo");
} */

int	main(int argc, char **argv)
{
	t_data	data;

	data.end = 0;
	//atexit(ft_leaks);
	if (argc < 5 || argc > 6)
		exit_error("invalid number of arguments\n", &data);
	ft_check_args(argc, argv, &data);
	ft_init(&data, argv);
	ft_create_threads(&data, argc, argv);
	end_subprocesses(&data);
	end_philos(&data);
	return (0);
}