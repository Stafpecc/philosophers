/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:09:54 by stafpec           #+#    #+#             */
/*   Updated: 2025/04/11 13:48:17 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (check_and_unlock_left(philo))
			return (EXIT_FAILURE);
		print_status(philo, "has taken a fork", BROWN);
		pthread_mutex_lock(philo->right_fork);
		if (check_and_unlock(philo))
			return (EXIT_FAILURE);
		print_status(philo, "has taken a fork", BROWN);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (check_and_unlock_right(philo))
			return (EXIT_FAILURE);
		print_status(philo, "has taken a fork", BROWN);
		pthread_mutex_lock(philo->left_fork);
		if (check_and_unlock(philo))
			return (EXIT_FAILURE);
		print_status(philo, "has taken a fork", BROWN);
	}
	return (EXIT_SUCCESS);
}

static void	eat(t_philo *philo)
{
	long	start_time;

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
		if (check_dead(philo) || !check_alive(philo))
		{
			unlock_forks(philo);
			return ;
		}
		usleep(100);
	}
	unlock_forks(philo);
}

static void	sleep_philo(t_philo *philo)
{
	long	start_time;

	if (check_dead(philo) || !check_alive(philo))
		return ;
	print_status(philo, "is sleeping", BLUE);
	start_time = current_time_in_ms();
	while (current_time_in_ms() - start_time < philo->data->time_to_sleep)
	{
		if (check_dead(philo) || !check_alive(philo))
			return ;
		usleep(100);
	}
}

static int	eat_sleep_routine(t_philo *philo)
{
	if (check_dead(philo))
		return (EXIT_FAILURE);
	if (take_forks(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	eat(philo);
	sleep_philo(philo);
	if (check_dead(philo) || !check_alive(philo))
		return (EXIT_FAILURE);
	print_status(philo, "is thinking", GREEN);
	return (EXIT_SUCCESS);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philosophers == 1)
		return (ret_lone_philo(philo));
	while (philo->data->num_times_each_philosopher_must_eat <= 0
		|| philo->times_ate < philo->data->num_times_each_philosopher_must_eat)
	{
		if (philo->data->is_dead || philo->data->philosophers_dead[philo->id])
			return (NULL);
		if (!check_alive(philo))
		{
			philo->data->is_dead = true;
			return (NULL);
		}
		if (eat_sleep_routine(philo) == EXIT_FAILURE)
			return (NULL);
	}
	philo->data->philosophers_dead[philo->id] = true;
	return (NULL);
}
