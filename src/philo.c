/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:56:18 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/06 19:26:45 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_init(t_data *data, int argc, char **argv)
{
	ft_init_data(data, argc, argv);
	ft_init_mutex(data);
	if (!ft_create_philo(data))
		exit_error("failed create philos\n", data);
	return (0);
}

int	ft_create_threads(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while( ++i < data->nbr_philo)
	{
		data->philos[i].last_meal = get_time();
		if (pthread_create(&data->philos[i].philo_id, NULL, routine, 
			&data->philos[i]))
			exit_error("a problem has ocurred creating threads", data);
	}
	check_dead(data, data->philos);
	pthread_mutex_unlock(&data->write);
	end_philos(data);
	return (0);
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

int	main(int argc, char **argv)
{
	t_data	data;
	
	data.end = 0;
	if (argc < 5 || argc > 6)
		exit_error("invalid number of arguments\n", &data);
	//ft_check_args(argc, argv, &data);
	ft_init(&data, argc, argv);
	ft_create_threads(&data);
	return (0);
}