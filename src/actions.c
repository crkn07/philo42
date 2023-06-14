/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:10:54 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/13 18:38:25 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *pointer)
{
	t_philo	*philo;
	//t_data	*data;

	philo = pointer;
	//data = philo->st_data;
	pthread_mutex_lock(philo->print_lock);
	pthread_mutex_unlock(philo->print_lock);
	if (philo->id % 2 == 0)
		ft_usleep(philo->eat_time / 50);
	pthread_mutex_lock(philo->print_lock);
	//pthread_mutex_lock(&data->meals);
	while (philo->end == 0)
	{
		pthread_mutex_unlock(philo->print_lock);
		//pthread_mutex_unlock(&data->meals);
		//pthread_mutex_lock(&data->meals);
//		printf("nº f: %d\n", data->nbr_philo);
		//pthread_mutex_unlock(philo->lock);
		//printf("nº: %d\n", philo->id);
		printf("entra\n");
		ft_eats(philo);
		//pthread_mutex_unlock(&data->meals);
		ft_usleep(philo->sleep_time);
		print_msg("think", philo);
		//pthread_mutex_lock(philo->lock);
		//pthread_mutex_lock(&data->meals);
		pthread_mutex_lock(philo->print_lock);
	}
	pthread_mutex_unlock(philo->print_lock);
	//pthread_mutex_unlock(&data->meals);
	return (NULL);
}


int	check_death(t_data *data, t_philo *philo)
{
	int	i = 0;

	//while (!data->max_meals)
	//{
		//i = -1;
		//{
			//while (++i < data->nbr_philo && !data->end)
			//{
				//pthread_mutex_lock(philo[i].lock);
				//pthread_mutex_lock(philo->print_lock);
				//pthread_mutex_lock(&data->meals);
				//printf("check death--%p\n", philo->lock);
	if ((get_time() - philo[i].last_meal) >= philo->death_time)
	{
		print_msg("died", &philo[i]);
		pthread_mutex_lock(philo->print_lock);
		//pthread_mutex_lock(&data->write);
		//printf("entra\n");
		data->end = 1;
		pthread_mutex_unlock(philo->print_lock);
		return (0);
	}
				//pthread_mutex_unlock(philo[i].lock);
				//pthread_mutex_unlock(&data->meals);
		//	}
			//if (data->end){
		//}
	i = 0;
		//pthread_mutex_lock(&data->meals);
	while (philo[i].nbr_meals && i < philo[i].nbr_meals
		&& philo[i].n_meals && philo[i].nbr_meals)
		i++;
		//pthread_mutex_unlock(&data->meals);
	pthread_mutex_lock(philo->print_lock);
	data->max_meals = (i == data->nbr_philo);
	pthread_mutex_unlock(philo->print_lock);
	return (1);
}

void	end_philos(t_data *data)
{
	int	i = 0;

	if (data->nbr_philo == 1)
		pthread_detach(data->philo_id[0]);
	else
	{
		//pthread_mutex_lock(data->philos[i].lock);
		while (i < data->nbr_philo)
		{
			pthread_mutex_unlock(data->philos[i].lock);
			pthread_join(data->philo_id[i], NULL);
			i++;
		}
		//pthread_mutex_unlock(data->philos[i].lock);

	}
	i = -1;
	while (++i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(data->print_lock);
		pthread_mutex_destroy(data->lock);
	}
	//pthread_mutex_destroy(&data->meals);
	//pthread_mutex_destroy(&data->write);
	ft_clear_data(data);
}

void	ft_eats(t_philo *philo)
{
	pthread_mutex_lock(&(philo->st_data->forks[philo->left_fork]));
	//printf("nº f: %d\n", philo->st_data->nbr_philo);
	print_msg("take a left fork", philo);
	pthread_mutex_lock(&(philo->st_data->forks[philo->right_fork]));
	//printf("entra en ft_eats\n");
	print_msg("take a right fork", philo);
	pthread_mutex_lock(philo->lock);
	philo->last_meal = get_time();
	print_msg("eat", philo);
	//printf("ft_eats--%d%p\n", philo->id, philo->lock);
	if (philo->nbr_meals != 0)
		philo->n_meals++;
	pthread_mutex_unlock(philo->lock);
	ft_usleep(philo->eat_time);
	pthread_mutex_unlock(&philo->st_data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->st_data->forks[philo->right_fork]);
	print_msg("sleep", philo);
}
