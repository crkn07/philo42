/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:10:54 by crtorres          #+#    #+#             */
/*   Updated: 2023/05/24 15:12:09 by crtorres         ###   ########.fr       */
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

