/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 02:27:27 by stafpec           #+#    #+#             */
/*   Updated: 2025/04/23 03:05:00 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks_helper(t_philo *philo, int left, int right)
{
	pthread_mutex_lock(&philo->data->forks_mutex[left]);
	philo->data->forks_available[left] = false;
	pthread_mutex_unlock(&philo->data->forks_mutex[left]);
	pthread_mutex_lock(&philo->data->forks_mutex[right]);
	philo->data->forks_available[right] = false;
	pthread_mutex_unlock(&philo->data->forks_mutex[right]);
	print_status(philo, "has taken a fork", BROWN);
	print_status(philo, "has taken a fork", BROWN);
}

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
			take_forks_helper(philo, left, right);
			run = false;
			pthread_mutex_unlock(&philo->data->forks_available_mutex);
			return (RETURN_SUCCESS);
		}
		pthread_mutex_unlock(&philo->data->forks_available_mutex);
		usleep(10);
	}
	return (RETURN_FAILURE);
}
