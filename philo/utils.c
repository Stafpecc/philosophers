/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:46:20 by stafpec           #+#    #+#             */
/*   Updated: 2025/04/22 19:04:02 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	unlock_forks(t_philo *philo)
{
	int	left;
	int	right;

	right = (philo->id + 1) % philo->data->num_philosophers;
	left = philo->id;
	pthread_mutex_lock(&philo->data->forks_available_mutex);
	pthread_mutex_lock(&philo->data->forks_mutex[left]);
	philo->data->forks_available[left] = true;
	pthread_mutex_unlock(&philo->data->forks_mutex[left]);
	pthread_mutex_lock(&philo->data->forks_mutex[right]);
	philo->data->forks_available[right] = true;
	pthread_mutex_unlock(&philo->data->forks_mutex[right]);
	pthread_mutex_unlock(&philo->data->forks_available_mutex);
}

void	*ret_lone_philo(t_philo *philo)
{
	lone_philo_routine(philo);
	return (NULL);
}

void	print_status(t_philo *philo, const char *status,
			const char *color)
{
	long long	timestamp_ms;
	int			do_print;

	do_print = 0;
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->is_dead || (philo->data->is_dead
			&& ft_strcmp(status, "died") == 0))
		do_print = 1;
	pthread_mutex_unlock(&philo->data->death_mutex);
	if (do_print)
	{
		pthread_mutex_lock(philo->print_mutex);
		timestamp_ms = current_time_in_ms() - philo->data->start_time;
		printf("%s%lld %d %s%s\n", color, timestamp_ms, philo->id + 1,
			status, RESET);
		pthread_mutex_unlock(philo->print_mutex);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
