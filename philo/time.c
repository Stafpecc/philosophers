/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:23:06 by stafpec           #+#    #+#             */
/*   Updated: 2025/04/20 13:54:22 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

struct timespec	get_timeout(long ms)
{
	struct timeval	tv;
	struct timespec	ts;

	gettimeofday(&tv, NULL);
	ts.tv_sec = tv.tv_sec + ms / 1000;
	ts.tv_nsec = tv.tv_usec * 1000 + (ms % 1000) * 1000000;
	if (ts.tv_nsec >= 1000000000)
	{
		ts.tv_sec += 1;
		ts.tv_nsec -= 1000000000;
	}
	return (ts);
}

void	custom_usleep(long duration, t_philo *philo)
{
	long	start;

	start = current_time_in_ms();
	while (current_time_in_ms() - start < duration)
	{
		if (!check_alive(philo))
			break ;
		usleep(100);
	}
}

static int	try_take_fork_ret_success(int fork_id, t_philo *philo, bool *run)
{
	philo->data->forks_available[fork_id] = false;
	pthread_mutex_unlock(&philo->data->forks_mutex);
	*run = false;
	return (EXIT_SUCCESS);
}

static int	try_take_fork_ret_failure(bool *run)
{
	*run = false;
	return (EXIT_FAILURE);
}

int	try_take_fork(int fork_id, t_philo *philo)
{
	long	start;
	long	now;
	bool	running;

	start = current_time_in_ms();
	running = true;
	while (running)
	{
		pthread_mutex_lock(&philo->data->forks_mutex);
		if (philo->data->forks_available[fork_id])
			return (try_take_fork_ret_success(fork_id, philo, &running));
		pthread_mutex_unlock(&philo->data->forks_mutex);
		if (!check_alive(philo))
			return (try_take_fork_ret_failure(&running));
		now = current_time_in_ms();
		if (now - start > 100)
			return (try_take_fork_ret_failure(&running));
		usleep(100);
	}
	return (EXIT_FAILURE);
}
