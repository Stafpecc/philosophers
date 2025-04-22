/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_unlock.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:48:56 by tarini            #+#    #+#             */
/*   Updated: 2025/04/22 15:44:28 by tarini           ###   ########.fr       */
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
