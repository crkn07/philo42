/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:50 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/05 17:20:59 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_msg(char *msg, t_philo *philo)
{
    int time;

    time = get_time() - philo->st_data->start_time;
    if (philo->st_data->end && !philo->st_data->max_meals)
    {
        printf("%d philo %d: %s\n", time, philo->position, msg);
    }
}
