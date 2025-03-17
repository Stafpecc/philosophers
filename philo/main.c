/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:48:05 by tarini            #+#    #+#             */
/*   Updated: 2025/03/17 20:03:07 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *hello(void *data)
{
	char str[] = "Hello World!";
	int	i;

	i = 0;
	while (i < 12)
	{
		pthread_mutex_lock(&mutex);
		fprintf(stderr, "\033[91m%c\033[0m", str[i]);
		usleep(100000);
		pthread_mutex_unlock(&mutex);
		i++;
	}
	fprintf(stderr, "\033[95m\nend1\033[0m\n");
	pthread_exit(data);
}

void *goodbye(void *data)
{
	char str[] = "Goodbye";
	int	i;

	i = 0;
	while (i < 7)
	{
		pthread_mutex_lock(&mutex);
		fprintf(stderr, "\033[92m%c\033[0m", str[i]);
		usleep(100000);
		pthread_mutex_unlock(&mutex);
		i++;
	}
	fprintf(stderr, "\033[95m\nend2\033[0m\n");
	pthread_exit(data);
}

int main(void)
{
	t_data *data;

	data = init_data(&data);
	pthread_t t1;
	pthread_t t2;
	char *s1;
	char *s2;

	pthread_create(&t1, NULL, hello, NULL);
	pthread_create(&t2, NULL, goodbye, NULL);
	pthread_mutex_destroy(&mutex);
	pthread_join(t1, (void **)&s1);
	pthread_join(t2, (void **)&s2);
		
	return (EXIT_SUCCESS);
}