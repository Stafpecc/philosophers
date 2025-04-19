/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:00:28 by tarini            #+#    #+#             */
/*   Updated: 2025/04/19 15:11:32 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  ______     ___   ___      ________      __           ______      
// /_____/\   /__/\ /__/\    /_______/\    /_/\         /_____/\              //
// \:::_ \ \  \::\ \\  \ \   \__.::._\/    \:\ \        \:::_ \ \    		  //
//  \:(_) \ \  \::\/_\ .\ \     \::\ \      \:\ \        \:\ \ \ \    		  //
//   \: ___\/   \:: ___::\ \    _\::\ \__    \:\ \____    \:\ \ \ \   		  //
//    \ \ \      \: \ \\::\ \  /__\::\__/\    \:\/___/\    \:\_\ \ \  		  //
//     \_\/       \__\/ \::\/  \________\/     \_____\/     \_____\/  	 	  //

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# define RESET   "\x1b[0m"
# define GREEN   "\x1b[32m"
# define ORANGE  "\x1b[38;5;214m"
# define BLUE    "\x1b[34m"
# define RED     "\x1b[31;4;1m"
# define BROWN   "\x1b[33;2;3m"

typedef enum e_bool
{
	DEAD,
	ALIVE
}	t_bool;

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	int				times_ate;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
    int				num_philosophers;
    long			time_to_die;
    long			time_to_eat;
    long			time_to_sleep;
    int				num_times_each_philosopher_must_eat;
	unsigned long	start_time;
    bool			is_dead;
    bool			*philosophers_dead;
    bool			*forks_available;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
    pthread_mutex_t	forks_mutex;
	t_philo			*philosophers;
}   t_data;



/******************************************************************************/
/*									FORK                                      */
/******************************************************************************/
void		unlock_forks(t_philo *philo);
int			check_and_unlock_left(t_philo *philo);
int			check_and_unlock_right(t_philo *philo);
int			check_and_unlock(t_philo *philo);

/******************************************************************************/
/*									DEAD                                      */
/******************************************************************************/
int			check_alive(t_philo *philo);
int			check_dead(t_philo *philo);
void		*ret_lock_unlock(t_philo *philo);
void		*ret_unlock(t_philo *philo);

/******************************************************************************/
/*									UTILS                                     */
/******************************************************************************/
int			ft_atoi(const char *str, int *error);
long long	current_time_in_ms(void);
void		print_status(t_philo *philo, const char *status, const char *color);
int			ft_strcmp(const char *s1, const char *s2);

/******************************************************************************/
/*									ROUTINE                                   */
/******************************************************************************/
void		*lone_philo_routine(t_philo *philo);
void		*routine(void *data);

/******************************************************************************/
/*									RETURN                                    */
/******************************************************************************/
void		*ret_lone_philo(t_philo *philo);

/******************************************************************************/
/*									DATA                                      */
/******************************************************************************/
int			init_data(t_data *data, int argc, char **argv);

/******************************************************************************/
/*									TIME                                      */
/******************************************************************************/
struct		timespec	get_timeout(long ms);
int			try_take_fork(int fork_id, t_philo *philo);
void		custom_usleep(long duration, t_philo *philo);

#endif
