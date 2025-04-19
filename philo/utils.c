/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:46:20 by stafpec           #+#    #+#             */
/*   Updated: 2025/04/19 14:44:29 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ret_lone_philo(t_philo *philo)
{
	lone_philo_routine(philo);
	return (NULL);
}

void unlock_forks(t_philo *philo)
{
    int left;
    int right;
	
	left = philo->id;
	right = (philo->id + 1) % philo->data->num_philosophers;
    pthread_mutex_lock(&philo->data->forks_mutex);
    philo->data->forks_available[left]  = true;
    philo->data->forks_available[right] = true;
    pthread_mutex_unlock(&philo->data->forks_mutex);
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
	int			do_print;

	do_print = 0;
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->is_dead || (philo->data->is_dead && ft_strcmp(status,
				"died") == 0))
		do_print = 1;
	pthread_mutex_unlock(&philo->data->death_mutex);
	if (do_print)
	{
		timestamp_ms = current_time_in_ms() - philo->data->start_time;
		pthread_mutex_lock(philo->print_mutex);
		printf("%s%lld %d %s%s\n", color, timestamp_ms, philo->id + 1, status,
			RESET);
		pthread_mutex_unlock(philo->print_mutex);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
