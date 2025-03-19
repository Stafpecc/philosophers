/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:48:05 by tarini            #+#    #+#             */
/*   Updated: 2025/03/18 16:28:42 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
    int i;
    t_data data;

    if (argc < 5 || argc > 6)
    {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return EXIT_FAILURE;
    }
    init_data(&data, argc, argv);
    i = 0;
    while (i < data.num_philosophers)
    {
        pthread_create(&data.philosophers[i].thread, NULL, routine, &data.philosophers[i]);
        i++;
    }
    i = 0;
    while (i < data.num_philosophers)
    {
        pthread_join(data.philosophers[i].thread, NULL);
        i++;
    }
    free_data(&data);
    return EXIT_SUCCESS;
}
