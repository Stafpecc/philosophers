/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:46:20 by stafpec           #+#    #+#             */
/*   Updated: 2025/04/13 18:43:50 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ret_lone_philo(t_philo *philo)
{
	lone_philo_routine(philo);
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
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(t_philo *philo, const char *status, const char *color)
{
	long long	timestamp_ms;

	timestamp_ms = current_time_in_ms() - philo->data->start_time;
	printf("%s%lld %d %s%s\n", color, timestamp_ms, philo->id + 1,
		status, RESET);
}
