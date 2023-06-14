/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:57:00 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/14 12:40:02 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct s_philo
{
	int				*end;
	int				n_meals;
	int				id;
	int				left_fork;
	int				right_fork;
	unsigned long	sleep_time;
	unsigned long	death_time;
	unsigned long	start_time;
	unsigned long	eat_time;
	unsigned long	last_meal;
	int				nbr_meals;
	unsigned long	tt_die;
	pthread_mutex_t *lock;
	pthread_mutex_t *print_lock;
	struct s_data	*st_data;
}t_philo;

typedef struct s_data
{
	int				max_meals;
	int				nbr_philo;
	int				dead;
	int				end;
	pthread_t		*philo_id;
	unsigned long	init_time;
	unsigned long	current_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	//pthread_mutex_t	meals;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*print_lock;
	//pthread_mutex_t	write;
}t_data;

void			exit_error(char *msg, t_data *data);
int				ft_atoi(const char *str, t_data *data);
int				ft_init_data(t_data *data, char **argv);
int				ft_init_mutex(t_data *data);
int				ft_create_philo(t_data *data, int argc, char **argv, int i);
int				ft_create_forks(t_data *data);
unsigned long	get_time(void);
void			*routine(void *pointer);
void			print_msg(char *msg, t_philo *philo);
int				ft_usleep(unsigned long time);
int				check_death(t_data *data, t_philo *philo);
void			end_philos(t_data *data);
void			ft_putstr_fd(char *s, int fd);
void			ft_clear_data(t_data *data);
void			ft_putchar_fd(char c, int fd);
void			ft_eats(t_philo *philo);
//int				ft_isdigit(char *c);

#endif