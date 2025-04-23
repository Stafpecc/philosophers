/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:48:05 by tarini            #+#    #+#             */
/*   Updated: 2025/04/23 03:13:28 by stafpec          ###   ########.fr       */
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
	int	i;

	if (!data)
		return ;
	if (data->forks_mutex)
	{
		i = 0;
		while (i < data->num_philosophers)
			pthread_mutex_destroy(&data->forks_mutex[i++]);
		free(data->forks_mutex);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks_available);
	free(data->philosophers_dead);
	free(data->philosophers);
}

int	print_ret(int nb, int i, char **argv)
{
	if (nb == PARSING)
		printf("%sError: invalid arguments%s\n", RED, RESET);
	else if (nb == USER_ARGS)
	{
		printf("%sUsage: %s %s<number_of_philosophers>%s ", RED,
			argv[0], RESET, BLUE);
		print_menu();
		printf("%s\n", RESET);
	}
	else if (nb == ALLOC)
		printf("%sError: memory allocation failed%s\n", RED, RESET);
	else if (nb == CREATE)
		printf("%sError: failed to create thread %d%s\n", RED, i, RESET);
	else if (nb == JOIN)
		printf("%sError: failed to join thread %d%s\n", RED, i, RESET);
	return (RETURN_FAILURE);
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
		if (pthread_create(&data->philosophers[i].thread, NULL, routine,
				&data->philosophers[i]) != 0)
			return (print_ret(CREATE, i, argv));
		i++;
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_join(data->philosophers[i].thread, NULL))
			return (print_ret(JOIN, i, argv));
		i++;
	}
	return (RETURN_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (print_ret(USER_ARGS, 0, argv));
	if (init_data(&data, argc, argv) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	if (data.num_times_each_philosopher_must_eat == 0)
	{
		free_data(&data);
		return (RETURN_SUCCESS);
	}
	free(data.philosophers_dead);
	data.philosophers_dead = malloc(sizeof(bool) * data.num_philosophers);
	if (!data.philosophers_dead)
	{
		free_data(&data);
		return (RETURN_FAILURE);
	}
	if (main_helper(&data, argv) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	free_data(&data);
	return (RETURN_SUCCESS);
}
