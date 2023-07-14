/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:57:00 by crtorres          #+#    #+#             */
/*   Updated: 2023/06/26 11:40:07 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//*===LIBRARIES===*/

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

//*===SETTINGS COLORS===*/
//*===Color font code===*/
# define BLACK   "\x1B[30m"
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define WHITE   "\x1B[37m"
# define ORANGE  "\x1B[38;2;255;128;0m"
# define ROSE    "\x1B[38;2;255;151;203m"
# define LBLUE   "\x1B[38;2;53;149;240m"
# define LGREEN  "\x1B[38;2;17;245;120m"
# define GRAY    "\x1B[38;2;176;174;174m"
//*===Color background code===*/
# define BG_BLACK   "\x1B[40m"
# define BG_RED     "\x1B[41m"
# define BG_GREEN   "\x1B[42m"
# define BG_YELLOW  "\x1B[43m"
# define BG_BLUE    "\x1B[44m"
# define BG_MAGENTA "\x1B[45m"
# define BG_CYAN    "\x1B[46m"
# define BG_WHITE   "\x1B[47m"
# define BG_ORANGE  "\x1B[48;2;255;128;0m"
# define BG_LBLUE   "\x1B[48;2;53;149;240m"
# define BG_LGREEN  "\x1B[48;2;17;245;120m"
# define BG_GRAY    "\x1B[48;2;176;174;174m"
# define BG_ROSE    "\x1B[48;2;255;151;203m"

# define RESET   "\x1b[0m"

//*===STRUCTURES===*/

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
	int				max_meals;
	int				all_meals;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*print_lock;
	struct s_data	*st_data;
}t_philo;

typedef struct s_data
{
	int				nbr_philo;
	int				end;
	int				nbr_philos_eat;
	pthread_t		*philo_id;
	unsigned long	init_time;
	unsigned long	current_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*print_lock;
}t_data;

//*===FUNCTIONS===*/

void			exit_error(char *msg, t_data *data);
int				ft_atoi(const char *str);
int				ft_init_data(t_data *data, char **argv);
int				ft_init_mutex(t_data *data, int i);
int				ft_create_philo(t_data *data, int argc, char **argv, int i);
int				ft_create_forks(t_data *data);
unsigned long	get_time(void);
void			*routine(void *pointer);
void			print_msg(char *msg, t_philo *philo);
int				ft_usleep(unsigned long time);
int				check_death(t_data *data, int i);
void			end_philos(t_data *data);
void			ft_putstr_fd(char *s, int fd);
void			ft_clear_data(t_data *data);
void			ft_eats(t_philo *philo);
void			exit_without_free(char *msg);

#endif