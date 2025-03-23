/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:09:54 by stafpec           #+#    #+#             */
/*   Updated: 2025/03/23 18:23:43 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*lone_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork", BROWN);
	usleep(philo->data->time_to_die * 1000);
	print_status(philo, "died", RED);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philosophers == 1)
	{
		lone_philo_routine(philo);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex);
		if (philo->data->is_dead || philo->data->philosophers_dead[philo->id])
		{
			pthread_mutex_unlock(&philo->data->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->mutex);
		if (!check_alive(philo))
		{
			pthread_mutex_lock(&philo->data->mutex);
			philo->data->is_dead = true;
			pthread_mutex_unlock(&philo->data->mutex);
			return (NULL);
		}
		eat_sleep_routine(philo);
	}
	return (NULL);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

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

void	eat_sleep_routine(t_philo *philo)
{
	long	start_time;

	if (check_dead(philo))
		return ;
	pthread_mutex_lock(philo->left_fork);
	if (check_and_unlock(philo))
		return ;
	print_status(philo, "has taken a fork", BROWN);
	pthread_mutex_lock(philo->right_fork);
	if (check_and_unlock(philo))
		return ;
	print_status(philo, "has taken a fork", BROWN);
	if (!check_alive(philo))
	{
		unlock_forks(philo);
		return ;
	}
	print_status(philo, "is eating", ORANGE);
	pthread_mutex_lock(&philo->data->mutex);
	philo->last_meal_time = current_time_in_ms();
	philo->times_ate++;
	pthread_mutex_unlock(&philo->data->mutex);
	start_time = current_time_in_ms();
	while (current_time_in_ms() - start_time < philo->data->time_to_eat)
	{
		if (check_and_unlock(philo))
			return ;
		usleep(100);
	}
	unlock_forks(philo);
	if (check_dead(philo))
		return ;
	print_status(philo, "is sleeping", BLUE);
	start_time = current_time_in_ms();
	while (current_time_in_ms() - start_time < philo->data->time_to_sleep)
	{
		if (check_dead(philo))
			return ;
		if (!check_alive(philo))
			return ;
		usleep(100);
	}
	if (check_dead(philo))
		return ;
	if (!philo->data->is_dead)
		print_status(philo, "is thinking", GREEN);
}
