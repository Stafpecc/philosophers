/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:09:54 by stafpec           #+#    #+#             */
/*   Updated: 2025/03/22 20:03:30 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *lone_philo_routine(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "has taken a fork", ORANGE);
    usleep(philo->data->time_to_die * 1000);
    print_status(philo, "died", RED);
    pthread_mutex_unlock(philo->left_fork);
    return NULL;
}

int check_alive(t_philo *philo)
{
    long last_meal_time;

    pthread_mutex_lock(&philo->data->mutex);
    last_meal_time = philo->last_meal_time;
    pthread_mutex_unlock(&philo->data->mutex);

    if (current_time_in_ms() - last_meal_time >= philo->data->time_to_die)
    {
        pthread_mutex_lock(&philo->data->mutex);
        philo->data->is_dead = 1;
        pthread_mutex_unlock(&philo->data->mutex);

        print_status(philo, "died", "RED");
        return 0;
    }
    return 1;
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    while (1)
    {
        if (!check_alive(philo))
            break;
        eat_sleep_routine(philo);
    }
    return NULL;
}

void eat_sleep_routine(t_philo *philo)
{
    long start_time;

    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "has taken a fork", ORANGE);
    pthread_mutex_lock(philo->right_fork);
    print_status(philo, "has taken a fork", ORANGE);
    print_status(philo, "is eating", ORANGE);
    pthread_mutex_lock(&philo->data->mutex);
    philo->last_meal_time = current_time_in_ms();
    philo->times_ate++;
    pthread_mutex_unlock(&philo->data->mutex);
    start_time = current_time_in_ms();
    while (current_time_in_ms() - start_time < philo->data->time_to_eat)
    {
        if (!check_alive(philo))
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
            return;
        }
        usleep(100);
    }
    
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    print_status(philo, "is sleeping", BLUE);
    start_time = current_time_in_ms();
    while (current_time_in_ms() - start_time < philo->data->time_to_sleep)
    {
        if (!check_alive(philo)) 
            return;
        usleep(100);
    }
    if (!philo->data->is_dead)
    {
        print_status(philo, "is thinking", GREEN);
    }
}
