/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 02:30:58 by stafpec           #+#    #+#             */
/*   Updated: 2025/04/23 03:13:55 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_forks_available(t_data *data)
{
	if (pthread_mutex_init(&data->forks_available_mutex, NULL) != 0)
	{
		printf("%sError: Failed to initialize forks_available_mutex%s\n",
			RED, RESET);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

static int	init_print(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		printf("%sError: Failed to initialize print_mutex%s\n", RED, RESET);
		pthread_mutex_destroy(&data->forks_available_mutex);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

static int	init_death(t_data *data)
{
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		printf("%sError: Failed to initialize death_mutex%s\n", RED, RESET);
		pthread_mutex_destroy(&data->forks_available_mutex);
		pthread_mutex_destroy(&data->print_mutex);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_mutex_init(&data->forks_mutex[i], NULL) != 0)
		{
			printf("%sError: Failed to initialize forks_mutex[%d]%s\n",
				RED, i, RESET);
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks_mutex[i]);
			pthread_mutex_destroy(&data->print_mutex);
			pthread_mutex_destroy(&data->death_mutex);
			return (RETURN_FAILURE);
		}
		i++;
	}
	return (RETURN_SUCCESS);
}

int	init_mutexes(t_data *data)
{
	if (init_forks_available(data) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	if (init_print(data) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	if (init_death(data) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	if (init_forks(data) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
