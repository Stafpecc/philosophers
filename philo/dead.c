/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:41:47 by tarini            #+#    #+#             */
/*   Updated: 2025/04/13 18:44:27 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_alive(t_philo *philo)
{
	long	last_meal_time;

	last_meal_time = philo->last_meal_time;
	if (philo->data->is_dead)
	{
		return (0);
	}
	if (current_time_in_ms() - last_meal_time >= philo->data->time_to_die)
	{
		philo->data->philosophers_dead[philo->id] = true;
		philo->data->is_dead = true;
		print_status(philo, "died", RED);
		return (0);
	}
	return (1);
}

int	check_dead(t_philo *philo)
{
	int	dead;

	dead = philo->data->is_dead;
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
