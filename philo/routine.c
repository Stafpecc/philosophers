/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:09:54 by stafpec           #+#    #+#             */
/*   Updated: 2025/03/18 16:45:15 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long current_time_in_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

static void print_status(t_philo *philo, const char *status, const char *color)
{
    pthread_mutex_lock(&philo->data->mutex);
    if (!philo->data->is_dead)
        printf("%s%ld Philosophe %d %s%s\n", color, current_time_in_ms(), philo->id + 1, status, RESET);
    pthread_mutex_unlock(&philo->data->mutex);
}

void *check_death(void *phi)
{
    t_philo *philo;

    philo = (t_philo *)phi;
    usleep(philo->data->time_to_die + 1);
    pthread_mutex_lock(&philo->data->mutex);
    if (!is_dead(philo, 0) && timestamp() - philo->last_meal_time >= (long)(philo->data->time_to_die))
    {
        print_status(philo, "died.", RED);
        is_dead(philo, 1);
    }    
    pthread_mutex_unlock(&philo->data->mutex);
    return (NULL);
}


void take_fork(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&(philo->left_fork));
        pthread_mutex_lock(&(philo->right_fork));
    }
    else
    {
        pthread_mutex_lock(&(philo->right_fork));
        pthread_mutex_lock(&(philo->left_fork));
    }
    print_status(philo, "has taken the left fork.", ORANGE);

    if (philo->data->num_philosophers == 1)
    {
        usleep(philo->data->time_to_die * 2);
        return;
    }

    print_status(philo, "has taken the right fork.", ORANGE);
}

void philo_eat(t_philo *philo)
{
    print_status(philo, "is eating.", ORANGE);

    pthread_mutex_lock(&(philo->data->time_to_eat));
    philo->last_meal_time = timestamp();
