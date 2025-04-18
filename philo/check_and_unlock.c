/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_unlock.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:48:56 by tarini            #+#    #+#             */
/*   Updated: 2025/04/19 14:43:40 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_and_unlock(t_philo *philo)
{
	if (check_dead(philo) || !check_alive(philo))
	{
		unlock_forks(philo);
		return (1);
	}
	return (0);
}

int	check_and_unlock_left(t_philo *philo)
{
	if (check_dead(philo) || !check_alive(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	check_and_unlock_right(t_philo *philo)
{
	if (check_dead(philo) || !check_alive(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	return (0);
}
