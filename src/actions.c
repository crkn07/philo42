/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:10:54 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/21 14:47:05 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = pointer;
	pthread_mutex_lock(philo->print_lock);
	pthread_mutex_unlock(philo->print_lock);
	if (philo->id % 2)
		ft_usleep(philo->eat_time);
	pthread_mutex_lock(philo->print_lock);
	while (*(philo->end) == 0)
	{
		pthread_mutex_unlock(philo->print_lock);
		ft_eats(philo);
		pthread_mutex_lock(philo->print_lock);
	}
	pthread_mutex_unlock(philo->print_lock);
	return (NULL);
}

int	check_death(t_data *data, int i)
{
	data->current_time = get_time() - data->philos->start_time;
	if ((data->current_time - data->philos[i].last_meal)
		> (data->philos[i].death_time + 1))
	{
		print_msg("died", &data->philos[i]);
		pthread_mutex_lock(data->print_lock);
		data->end = 1;
		pthread_mutex_unlock(data->print_lock);
		return (0);
	}
	if (data->philos[i].n_meals == data->philos[i].max_meals
		&& data->philos[i].all_meals == 0)
	{
		data->philos[i].all_meals = 1;
		if (++data->nbr_philos_eat == data->nbr_philo)
		{
			pthread_mutex_lock(data->print_lock);
			data->end = 1;
			pthread_mutex_unlock(data->print_lock);
			return (0);
		}
	}
	return (1);
}

void	end_philos(t_data *data)
{
	int	i;

	i = 0;
	if (data->nbr_philo == 1)
		pthread_detach(data->philo_id[0]);
	else
	{
		while (i < data->nbr_philo)
			{
				pthread_mutex_unlock(data->philos[i].lock);
				pthread_join(data->philo_id[i], NULL);
				i++;
			}
	}
	i = -1;
	while (++i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&(data->print_lock[i]));
		pthread_mutex_destroy(&(data->lock[i]));
	}
	ft_clear_data(data);
}

void	ft_eats(t_philo *philo)
{
	pthread_mutex_lock(&(philo->st_data->forks[philo->left_fork]));
	print_msg("take a left fork", philo);
	pthread_mutex_lock(&(philo->st_data->forks[philo->right_fork]));
	print_msg("take a right fork", philo);
	pthread_mutex_lock(philo->lock);
	philo->last_meal = get_time() - philo->start_time;
	print_msg("eat", philo);
	if (philo->max_meals != 0)
		philo->n_meals++;
	pthread_mutex_unlock(philo->lock);
	ft_usleep(philo->eat_time);
	pthread_mutex_unlock(&philo->st_data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->st_data->forks[philo->right_fork]);
	print_msg("sleep", philo);
	ft_usleep(philo->sleep_time);
	print_msg("think", philo);
}
