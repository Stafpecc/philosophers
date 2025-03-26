/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:09:54 by stafpec           #+#    #+#             */
/*   Updated: 2025/03/26 21:06:45 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philosophers == 1)
		return (ret_lone_philo(philo));
	while (philo->data->num_times_each_philosopher_must_eat <= 0
		|| philo->times_ate < philo->data->num_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->data->mutex);
		if (philo->data->is_dead || philo->data->philosophers_dead[philo->id])
			return (ret_unlock_null(philo));
		pthread_mutex_unlock(&philo->data->mutex);
		if (!check_alive(philo))
		{
			pthread_mutex_lock(&philo->data->mutex);
			philo->data->is_dead = true;
			return (ret_unlock_null(philo));
		}
		eat_sleep_routine(philo);
	}
	pthread_mutex_lock(&philo->data->mutex);
	philo->data->philosophers_dead[philo->id] = true;
	pthread_mutex_unlock(&philo->data->mutex);
	return (NULL);
}

static void take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (check_and_unlock(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	print_status(philo, "has taken a fork", BROWN);

	pthread_mutex_lock(philo->right_fork);
	if (check_and_unlock(philo))
	{
		unlock_forks(philo);
		return ;
	}
	print_status(philo, "has taken a fork", BROWN);
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

void	eat_sleep_routine(t_philo *philo)
{
	if (check_dead(philo))
		return ;
	take_forks(philo);
	eat(philo);
	sleep_philo(philo);
	if (check_dead(philo) || !check_alive(philo))
		return ;
	print_status(philo, "is thinking", GREEN);
}
