/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:48:05 by tarini            #+#    #+#             */
/*   Updated: 2025/03/23 18:04:30 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	int		i;
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat \
		time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (EXIT_FAILURE);
	}
	init_data(&data, argc, argv);
	data.philosophers_dead = malloc(sizeof(bool) * data.num_philosophers);
	i = 0;
	while (i < data.num_philosophers)
	{
		data.philosophers_dead[i] = false;
		i++;
	}
	i = 0;
	while (i < data.num_philosophers)
	{
		pthread_create(&data.philosophers[i].thread, NULL, routine,
			&data.philosophers[i]);
		i++;
	}
	i = 0;
	while (i < data.num_philosophers)
	{
		pthread_join(data.philosophers[i].thread, NULL);
		i++;
	}
	free(data.philosophers_dead);
	free_data(&data);
	return (EXIT_SUCCESS);
}
