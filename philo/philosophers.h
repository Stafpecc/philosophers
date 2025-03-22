/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:00:28 by tarini            #+#    #+#             */
/*   Updated: 2025/03/22 20:02:07 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define RED     "\x1b[31m"

typedef struct s_philo
{
    int id;
    long last_meal_time;
    int times_ate;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_data *data;
} t_philo;

typedef struct s_data
{
    int num_philosophers;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int num_times_each_philosopher_must_eat;
    bool is_dead;
    unsigned long	start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t mutex;
    t_philo *philosophers;
} t_data;

void eat_sleep_routine(t_philo *philo);
void *lone_philo_routine(t_philo *philo);
void *routine(void *data);
void init_data(t_data *data, int argc, char **argv);
void free_data(t_data *data);
long long	timestamp(void);
long long current_time_in_ms();
void	sign(char *str, unsigned int *num, size_t *start, int n);
char	*ft_itoa(int n);
void print_status(t_philo *philo, const char *status, const char *color);



#endif
