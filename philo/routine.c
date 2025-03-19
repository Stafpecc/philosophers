/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:09:54 by stafpec           #+#    #+#             */
/*   Updated: 2025/03/19 15:31:23 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void eat_sleep_routine(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "Taking a fork", ORANGE);
    pthread_mutex_lock(philo->right_fork);
    print_status(philo, "Taking a fork", ORANGE);
    print_status(philo, "Eating", ORANGE);
    pthread_mutex_lock(&philo->data->mutex);
    philo->last_meal_time = current_time_in_ms();
    pthread_mutex_unlock(&philo->data->mutex);
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_lock(&philo->data->mutex);
    philo->times_ate++;
    pthread_mutex_unlock(&philo->data->mutex);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    print_status(philo, "Sleeping", BLUE);
    usleep(philo->data->time_to_sleep * 1000);
}

void think_routine(t_philo *philo)
{
    long time_to_think;
    pthread_mutex_lock(&philo->data->mutex);
    time_to_think = (philo->data->time_to_die - (current_time_in_ms() - philo->last_meal_time) - philo->data->time_to_eat) / 2;
    pthread_mutex_unlock(&philo->data->mutex);
    if (time_to_think < 0)
        time_to_think = 0;
    if (time_to_think > 600)
        time_to_think = 200;
    print_status(philo, "Thinking", GREEN);
    usleep(time_to_think * 1000);
}

void *lone_philo_routine(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "Taking a fork", ORANGE);
    usleep(philo->data->time_to_die * 1000);
    print_status(philo, "Dying", RED);
    pthread_mutex_unlock(philo->left_fork);
    return NULL;
}

void *routine(void *data)
{
    t_philo *philo = (t_philo *)data;
    
    pthread_mutex_lock(&philo->data->mutex);
    philo->last_meal_time = current_time_in_ms();
    pthread_mutex_unlock(&philo->data->mutex);
    
    if (philo->data->num_philosophers == 1)
        return lone_philo_routine(philo);
    if (philo->id % 2)
        think_routine(philo);
    while (!philo->data->is_dead)
    {
        eat_sleep_routine(philo);
        think_routine(philo);
    }
    return NULL;
}
