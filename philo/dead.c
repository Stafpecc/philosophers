/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:41:47 by tarini            #+#    #+#             */
/*   Updated: 2025/04/17 17:55:07 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_alive(t_philo *philo)
{
	long last_meal_time;

	pthread_mutex_lock(&philo->data->death_mutex);

	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (DEAD);
	}

	last_meal_time = philo->last_meal_time;

	if (current_time_in_ms() - last_meal_time >= philo->data->time_to_die)
	{
		philo->data->philosophers_dead[philo->id] = true;
		philo->data->is_dead = true;
		pthread_mutex_unlock(&philo->data->death_mutex);
		print_status(philo, "died", RED);
		return (DEAD);
	}

	pthread_mutex_unlock(&philo->data->death_mutex);
	return (ALIVE);
}

int	check_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->data->death_mutex);
	dead = philo->data->is_dead;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (dead);
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
