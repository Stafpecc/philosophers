/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:41:47 by tarini            #+#    #+#             */
/*   Updated: 2025/03/26 19:15:13 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_and_unlock(t_philo *philo)
{
	if (check_dead(philo))
	{
		unlock_forks(philo);
		return (1);
	}
	if (!check_alive(philo))
	{
		unlock_forks(philo);
		return (1);
	}
	return (0);
}

int	check_alive(t_philo *philo)
{
	long	last_meal_time;

	pthread_mutex_lock(&philo->data->mutex);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->mutex);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (0);
	}
	if (current_time_in_ms() - last_meal_time >= philo->data->time_to_die)
	{
		philo->data->philosophers_dead[philo->id] = true;
		philo->data->is_dead = true;
		pthread_mutex_unlock(&philo->data->death_mutex);
		print_status(philo, "died", RED);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (1);
}

int	check_dead(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->data->death_mutex);
	i = 0;
	while (i < philo->data->num_philosophers)
	{
		if (philo->data->philosophers_dead[i])
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

void	*lone_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork", BROWN);
	usleep(philo->data->time_to_die * 1000);
	print_status(philo, "died", RED);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
