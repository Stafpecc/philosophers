/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:28:34 by stafpec           #+#    #+#             */
/*   Updated: 2025/03/26 15:01:12 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_arguments(t_data *data, int argc, char **argv)
{
	int	error;

	data->num_philosophers = ft_atoi(argv[1], &error);
	data->time_to_die = ft_atoi(argv[2], &error);
	data->time_to_eat = ft_atoi(argv[3], &error);
	data->time_to_sleep = ft_atoi(argv[4], &error);
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
	data->philosophers = malloc(sizeof(t_philo) * data->num_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	data->philosophers_dead = malloc(sizeof(bool) * data->num_philosophers);
	if (!data->philosophers || !data->forks || !data->philosophers_dead)
		return (EXIT_FAILURE);
	memset(data->forks, 0, sizeof(pthread_mutex_t) * data->num_philosophers);
	memset(data->philosophers_dead, 0, sizeof(bool) * data->num_philosophers);
	return (EXIT_SUCCESS);
}

void	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].last_meal_time = current_time_in_ms();
		data->philosophers[i].times_ate = 0;
		data->philosophers[i].data = data;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1)
			% data->num_philosophers];
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
