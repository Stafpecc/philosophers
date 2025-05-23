/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:23:06 by stafpec           #+#    #+#             */
/*   Updated: 2025/04/22 18:09:58 by tarini           ###   ########.fr       */
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

long long	current_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
