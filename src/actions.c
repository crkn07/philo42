/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:10:54 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/05 17:36:43 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = pointer;
	philo->tt_die = philo->st_data->death_time + get_time();
	
}

void	*count_meals(void *pointer)
{
	t_philo	*philo;

	philo = pointer;
	pthread_mutex_lock(&philo->st_data->lock);
	philo->st_data->end++;
	philo->count_meal++;
	pthread_mutex_unlock(&philo->st_data->lock);
}

void	*supervisor(void *pointer)
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
}

void	check_dead(t_data *data, t_philo **philo)
{
	int	i;

	while (!data->max_meals)
	{
		i = -1;
		{
			while (++i < data->nbr_philo && !data->end)
			{
				pthread_mutex_lock(&data->meals);
				if ((int)(get_time() - philo[i]->last_meal) >= data->death_time)
				{
					pthread_mutex_lock(&data->write);
					print_msg("died", &philo[i]);
				}
				pthread_mutex_unlock(&data->meals);
			}
			if (data->end)
				break;
		}
		i = 0;
		while (data->nbr_meals && i < data->nbr_meals 
			&& philo[i]->n_meals && data->nbr_meals)
			i++;
		data->max_meals = (i ==data->nbr_philo);
	}
}

void	end_philos()