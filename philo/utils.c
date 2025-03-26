/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:46:20 by stafpec           #+#    #+#             */
/*   Updated: 2025/03/26 15:02:56 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ret_unlock_null(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->mutex);
	return (NULL);
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

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

long long	current_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

void	print_status(t_philo *philo, const char *status, const char *color)
{
	long long	timestamp_ms;

	pthread_mutex_lock(&philo->data->mutex);
	timestamp_ms = current_time_in_ms() - philo->data->start_time;
	printf("%s%lld %d %s%s\n", color, timestamp_ms, philo->id + 1,
		status, RESET);
	pthread_mutex_unlock(&philo->data->mutex);
}
