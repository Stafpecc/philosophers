/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:48:05 by tarini            #+#    #+#             */
/*   Updated: 2025/04/22 15:44:32 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_menu(void)
{
	printf("%s<time_to_die> <time_to_eat> \
<time_to_sleep>%s ", GREEN, RESET);
	printf("%s[<number_of_times_each_philosopher_must_eat\
>]%s\n", ORANGE, RESET);
	printf("\n%s<number_of_philosophers>%s	: Number of philosophers \
(1-200)\n", BLUE, RESET);
	printf("\n%s<time_to_die>%s			: Time before a philosopher dies \
(ms, > 0)\n", GREEN, RESET);
	printf("%s<time_to_eat>%s			: Time a philosopher takes to eat \
(ms, > 0)\n", GREEN, RESET);
	printf("%s<time_to_sleep>%s			: Time a philosopher sleeps \
(ms, > 0)\n", GREEN, RESET);
	printf("\n%s[<meals_required>]%s		: (Optional) Number of meals \
before stopping\n", ORANGE, RESET);
}

static void	free_data(t_data *data)
{
	if (!data)
		return ;
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->forks_mutex);
	free(data->forks_available);
	free(data->philosophers_dead);
	free(data->philosophers);
}

static int	print_ret(int nb, int i, char **argv)
{
	if (nb == 1)
		printf("%sError: failed to join thread %d%s\n", RED, i, RESET);
	else if (nb == 2)
		printf("%sError: invalid arguments%s\n", RED, RESET);
	else if (nb == 3)
	{
		printf("%sUsage: %s %s%s\
		<number_of_philosophers>%s ", RED, argv[0], RESET, BLUE, RESET);
		print_menu();
	}
	return (EXIT_FAILURE);
}

static int	main_helper(t_data *data, char **argv)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		data->philosophers_dead[i] = false;
		i++;
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_create(&data->philosophers[i].thread, NULL, routine,
			&data->philosophers[i]);
		i++;
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_join(data->philosophers[i].thread, NULL))
			return (print_ret(1, i, argv));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (print_ret(3, 0, argv));
	if (init_data(&data, argc, argv) == EXIT_FAILURE)
		return (print_ret(2, 0, argv));
	if (data.num_times_each_philosopher_must_eat == 0)
	{
		free_data(&data);
		return (EXIT_SUCCESS);
	}
	free(data.philosophers_dead);
	data.philosophers_dead = malloc(sizeof(bool) * data.num_philosophers);
	if (!data.philosophers_dead)
	{
		free_data(&data);
		return (EXIT_FAILURE);
	}
	if (main_helper(&data, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	free_data(&data);
	return (EXIT_SUCCESS);
}
