/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:28:34 by stafpec           #+#    #+#             */
/*   Updated: 2025/03/19 15:41:08 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void init_data(t_data *data, int argc, char **argv)
{
    int i;

    data->num_philosophers = atoi(argv[1]);
    data->time_to_die = atol(argv[2]);
    data->time_to_eat = atol(argv[3]);
    data->time_to_sleep = atol(argv[4]);
    data->num_times_each_philosopher_must_eat = argc == 6 ? atoi(argv[5]) : -1;
    data->is_dead = false;
    data->philosophers = malloc(sizeof(t_philo) * data->num_philosophers);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
    memset(data->forks, 0, sizeof(pthread_mutex_t) * data->num_philosophers);
    pthread_mutex_init(&data->mutex, NULL);

    i = 0;
    while (i < data->num_philosophers)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        data->philosophers[i].id = i;
        data->philosophers[i].last_meal_time = current_time_in_ms();
        data->philosophers[i].times_ate = 0;
        data->philosophers[i].data = data;
        data->philosophers[i].left_fork = &data->forks[i];
        data->philosophers[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
        i++;
    }
}

void free_data(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philosophers)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->mutex);
    free(data->philosophers);
    free(data->forks);
}