/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:09:54 by stafpec           #+#    #+#             */
/*   Updated: 2025/04/23 03:05:00 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eat(t_philo *philo)
{
	if (!check_alive(philo))
	{
		unlock_forks(philo);
		return ;
	}
	print_status(philo, "is eating", ORANGE);
	philo->last_meal_time = current_time_in_ms();
	philo->times_ate++;
	custom_usleep(philo->data->time_to_eat, philo);
	unlock_forks(philo);
}

static void	sleep_philo(t_philo *philo)
{
	if (check_dead(philo) || !check_alive(philo))
		return ;
	print_status(philo, "is sleeping", BLUE);
	custom_usleep(philo->data->time_to_sleep, philo);
	usleep(500);
}

static int	eat_sleep_routine(t_philo *philo)
{
	if (check_dead(philo))
		return (RETURN_FAILURE);
	if (take_forks(philo) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	eat(philo);
	sleep_philo(philo);
	if (check_dead(philo) || !check_alive(philo))
		return (RETURN_FAILURE);
	print_status(philo, "is thinking", GREEN);
	return (RETURN_SUCCESS);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philosophers == 1)
		return (ret_lone_philo(philo));
	print_status(philo, "is thinking", GREEN);
	if (philo->id % 2 == 1)
		usleep((philo->data->time_to_eat / 2) * 1000);
	usleep(philo->id * 100);
	while (philo->data->num_times_each_philosopher_must_eat <= 0
		|| philo->times_ate < philo->data->num_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->is_dead || philo->data->philosophers_dead[philo->id])
			return (ret_unlock(philo));
		pthread_mutex_unlock(&philo->data->death_mutex);
		if (!check_alive(philo))
			return (ret_lock_unlock(philo));
		if (eat_sleep_routine(philo) == RETURN_FAILURE)
			return (NULL);
	}
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->data->philosophers_dead[philo->id] = true;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (NULL);
}
