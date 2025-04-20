/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:06:49 by stafpec           #+#    #+#             */
/*   Updated: 2025/04/20 14:10:21 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ret_left(t_philo *philo, int left)
{
	pthread_mutex_lock(&philo->data->forks_mutex);
	philo->data->forks_available[left] = true;
	pthread_mutex_unlock(&philo->data->forks_mutex);
	return (EXIT_FAILURE);
}

static int	ret_right(t_philo *philo, int right)
{
	pthread_mutex_lock(&philo->data->forks_mutex);
	philo->data->forks_available[right] = true;
	pthread_mutex_unlock(&philo->data->forks_mutex);
	return (EXIT_FAILURE);
}

int	take_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->data->num_philosophers;
	if (philo->id % 2 == 0)
	{
		if (try_take_fork(left, philo) || try_take_fork(right, philo))
			return (ret_left(philo, left));
	}
	else
	{
		if (try_take_fork(right, philo) || try_take_fork(left, philo))
			return (ret_right(philo, right));
	}
	print_status(philo, "has taken a fork", BROWN);
	print_status(philo, "has taken a fork", BROWN);
	return (EXIT_SUCCESS);
}
