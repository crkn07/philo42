/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:56:18 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/05 17:30:16 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_init(t_data *data, int argc, char **argv)
{
	ft_init_data(data, argc, argv);
	if (!ft_init_mutex(data))
		exit_error("failed init mutex\n", data);
	if (!ft_create_philo(data));
		exit_error("failed create philos\n", data);
}

int	ft_create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while( i < data->nbr_philo)
	{
		data->philos[i].last_meal = get_time();
		if (pthread_create(&data->philos[i].philo_id, NULL, routine, 
			&data->philos[i]))
			return (0);
	}
	check_dead(data, data->philos);
	pthread_mutex_unlock(&data->write);
}

int	ft_check_args(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (argc < 5 || argc > 6)
		exit_error("invalid number of arguments\n", data);
	while (j < argc)
	{
		while (argv[j][++i])
		{
			if (argv[j][i] >= '0' && argv[j][i] <= '9')
				return (ft_atoi(argv[j], data));
			else
				exit_error("invalid type of argument\n", data);
		}
		j++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	ft_check_args(argc, argv, data);
	ft_init(&data, argc, argv);
	ft_create_threads(&data);
	
}