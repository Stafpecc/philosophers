/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:23:06 by stafpec           #+#    #+#             */
/*   Updated: 2025/04/21 18:42:49 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
