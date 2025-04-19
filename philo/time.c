/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:23:06 by stafpec           #+#    #+#             */
/*   Updated: 2025/04/19 15:12:11 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

struct timespec	get_timeout(long ms)
{
	struct timeval  tv;
	struct timespec ts;

	gettimeofday(&tv, NULL);
	ts.tv_sec  = tv.tv_sec + ms / 1000;
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
			break;
		usleep(100);
	}
}

int	try_take_fork(int fork_id, t_philo *philo)
{
    long start_time;
    long timeout = 50000;

    start_time = current_time_in_ms();
    while (1)
    {
        pthread_mutex_lock(&philo->data->forks_mutex);

        if (philo->data->forks_available[fork_id])
        {
            philo->data->forks_available[fork_id] = false;
            pthread_mutex_unlock(&philo->data->forks_mutex);
            return (EXIT_SUCCESS);
        }

        pthread_mutex_unlock(&philo->data->forks_mutex);

        if (!check_alive(philo))
            return (EXIT_FAILURE);

        if ((current_time_in_ms() - start_time) >= timeout)
            return (EXIT_FAILURE);

        usleep(100);
    }
}