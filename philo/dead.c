/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:41:47 by tarini            #+#    #+#             */
/*   Updated: 2025/03/26 14:50:18 by tarini           ###   ########.fr       */
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

static int	check_alive_helper(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_philosophers)
	{
		if (philo->data->philosophers_dead[i])
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_alive(t_philo *philo)
{
	long	last_meal_time;

	pthread_mutex_lock(&philo->data->mutex);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->mutex);
	if (current_time_in_ms() - last_meal_time >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->mutex);
		philo->data->philosophers_dead[philo->id] = true;
		philo->data->is_dead = true;
		pthread_mutex_unlock(&philo->data->mutex);
		print_status(philo, "died", RED);
		return (0);
	}
	pthread_mutex_lock(&philo->data->death_mutex);
	if (check_alive_helper(philo) == 0)
		return (0);
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
