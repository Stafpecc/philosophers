/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:28:34 by stafpec           #+#    #+#             */
/*   Updated: 2025/04/19  by <your_name>          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_arguments(t_data *data, int argc, char **argv)
{
	int	error;

	error = 0;
	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	data->num_philosophers = ft_atoi(argv[1], &error);
	if (error || data->num_philosophers < 1)
		return (EXIT_FAILURE);
	data->time_to_die = ft_atoi(argv[2], &error);
	if (error)
		return (EXIT_FAILURE);
	data->time_to_eat = ft_atoi(argv[3], &error);
	if (error)
		return (EXIT_FAILURE);
	data->time_to_sleep = ft_atoi(argv[4], &error);
	if (error)
		return (EXIT_FAILURE);
	if (argc == 6)
		data->num_times_each_philosopher_must_eat = ft_atoi(argv[5], &error);
	else
		data->num_times_each_philosopher_must_eat = -1;
	if (error)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	allocate_resources(t_data *data)
{
	int i;

	data->philosophers = malloc(sizeof(t_philo) * data->num_philosophers);
	if (!data->philosophers)
		return (EXIT_FAILURE);
	data->forks_available = malloc(sizeof(bool) * data->num_philosophers);
	if (!data->forks_available)
	{
		free(data->philosophers);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		data->forks_available[i] = true;
		i++;
	}
	data->philosophers_dead = malloc(sizeof(bool) * data->num_philosophers);
	if (!data->philosophers_dead)
	{
		free(data->philosophers);
		free(data->forks_available);
		return (EXIT_FAILURE);
	}
	memset(data->philosophers_dead, 0, sizeof(bool) * data->num_philosophers);
	return (EXIT_SUCCESS);
}

void	init_mutexes(t_data *data)
{
	pthread_mutex_init(&data->forks_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
}

void	init_philosophers(t_data *data)
{
	int i;
	long now;

	now = current_time_in_ms();
	i = 0;
	while (i < data->num_philosophers)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].last_meal_time = now;
		data->philosophers[i].times_ate = 0;
		data->philosophers[i].data = data;
		data->philosophers[i].print_mutex = &data->print_mutex;
		i++;
	}
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (parse_arguments(data, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data->is_dead = false;
	data->start_time = current_time_in_ms();
	if (allocate_resources(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_mutexes(data);
	init_philosophers(data);
	return (EXIT_SUCCESS);
}
