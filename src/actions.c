/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:10:54 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/06 20:14:58 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *pointer)
{
	t_philo	*philo;
	t_data	*data;

	philo = pointer;
	data = philo->st_data;
	if (philo->id % 2 && data->nbr_philo > 1)
		ft_usleep(data->eat_time);
	pthread_mutex_lock(&data->meals);
	while (!data->end && !data->max_meals)
	{
		//printf("entra \n");
		ft_eats(philo);
		pthread_mutex_unlock(&data->meals);
		ft_usleep(philo->st_data->sleep_time);
		pthread_mutex_lock(&data->meals);
		print_msg("think", philo);
	}
	pthread_mutex_unlock(&data->meals);
	return (NULL);
}

/* void	*count_meals(void *pointer)
{
	t_philo	*philo;

	philo = pointer;
	pthread_mutex_lock(&philo->st_data->lock);
	philo->st_data->end++;
	philo->count_meal++;
	pthread_mutex_unlock(&philo->st_data->lock);
} */

/* void	*supervisor(void *pointer)
{
	t_philo 		*philo;
	unsigned long	time;

	philo = pointer;
	time = philo->st_data->start_time;
	while (philo->st_data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->tt_die && philo->eating == 0)
		{
			pthread_mutex_lock(&philo->st_data->write);
			if (philo->st_data->dead == 0)
			{
				printf("%ld %d is died\n", time, philo->id);
				philo->st_data->dead = 1;
			}
			pthread_mutex_unlock(&philo->st_data->write);
		}
		if (philo->count_meal = philo->st_data->nbr_meals)
			count_meals(philo);
		pthread_mutex_unlock(&philo->lock);
	}
} */

void	check_dead(t_data *data, t_philo *philo)
{
	int	i;

	while (!data->max_meals)
	{
		i = -1;
		{
			while (++i < data->nbr_philo && !data->end)
			{
				pthread_mutex_lock(&data->meals);
				if ((get_time() - philo[i].last_meal) >= data->death_time)
				{
					pthread_mutex_lock(&data->write);
					print_msg("died", &philo[i]);
					data->end = 1;
				}
				pthread_mutex_unlock(&data->meals);
			}
			if (data->end)
				break;
		}
		i = 0;
		pthread_mutex_lock(&data->meals);
		while (data->nbr_meals && i < data->nbr_meals
			&& philo[i].n_meals && data->nbr_meals)
			i++;
		data->max_meals = (i ==data->nbr_philo);
		pthread_mutex_unlock(&data->meals);
	}
}

void	end_philos(t_data *data)
{
	int	i;

	if (data->nbr_philo == 1)
		pthread_detach(data->philos[0].philo_id);
	else
	{
		i = 0;
		while (i < data->nbr_philo)
		{
		pthread_join(data->philos[i].philo_id, NULL);
		i++;
		}
	}
	i = -1;
	while (++i < data->nbr_philo)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->meals);
	pthread_mutex_destroy(&data->write);
	ft_clear_data(data);
}

void	ft_eats(t_philo *philo)
{
	pthread_mutex_lock(&philo->st_data->forks[philo->left_fork]);
	print_msg("take a left fork", philo);
	pthread_mutex_lock(&philo->st_data->forks[philo->right_fork]);
	print_msg("take a right fork", philo);
	print_msg("eat", philo);
	philo->last_meal = get_time();
	ft_usleep(philo->st_data->sleep_time);
	philo->n_meals++;
	pthread_mutex_unlock(&philo->st_data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->st_data->forks[philo->right_fork]);
	print_msg("sleep", philo);
}
