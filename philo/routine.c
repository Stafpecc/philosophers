/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:09:54 by stafpec           #+#    #+#             */
/*   Updated: 2025/04/22 19:03:41 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_philo *philo)
{
	int		left;
	int		right;
	bool	run;

	run = true;
	right = (philo->id + 1) % philo->data->num_philosophers;
	left = philo->id;
	while (run)
	{
		pthread_mutex_lock(&philo->data->forks_available_mutex);
		if (philo->data->forks_available[left]
			&& philo->data->forks_available[right])
		{
			pthread_mutex_lock(&philo->data->forks_mutex[left]);
			philo->data->forks_available[left] = false;
			pthread_mutex_unlock(&philo->data->forks_mutex[left]);
			pthread_mutex_lock(&philo->data->forks_mutex[right]);
			philo->data->forks_available[right] = false;
			pthread_mutex_unlock(&philo->data->forks_mutex[right]);
			print_status(philo, "has taken a fork", BROWN);
			print_status(philo, "has taken a fork", BROWN);
			run = false;
			pthread_mutex_unlock(&philo->data->forks_available_mutex);
			return (EXIT_SUCCESS);
		}
		pthread_mutex_unlock(&philo->data->forks_available_mutex);
		usleep(10);
	}
	return (EXIT_FAILURE);
}

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
		if (eat_sleep_routine(philo) == EXIT_FAILURE)
			return (NULL);
	}
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->data->philosophers_dead[philo->id] = true;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (NULL);
}
