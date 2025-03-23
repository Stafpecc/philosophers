/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:41:47 by tarini            #+#    #+#             */
/*   Updated: 2025/03/23 18:02:39 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_alive(t_philo *philo)
{
	int		i;
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
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}
