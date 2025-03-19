/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:46:20 by stafpec           #+#    #+#             */
/*   Updated: 2025/03/19 15:42:25 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long current_time_in_ms()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

static size_t	ft_numlen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	sign(char *str, unsigned int *num, size_t *start, int n)
{
	if (n < 0)
	{
		str[0] = '-';
		*num = -n;
		*start = 1;
	}
	else
	{
		*num = n;
		*start = 0;
	}
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			len;
	unsigned int	num;
	size_t			start;

	len = ft_numlen(n);
	str = calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	sign(str, &num, &start, n);
	while (len > start)
	{
		str[len - 1] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	return (str);
}

void print_status(t_philo *philo, const char *status, const char *color)
{
    pthread_mutex_lock(&philo->data->mutex);
    char timestamp;

    timestamp = ft_itoa(current_time_in_ms() - philo->data->start_time);
    if (!philo->data->is_dead)
        printf("%s%ld philosopher_%d %s%s\n", color, current_time_in_ms(), philo->id + 1, status, RESET);
    pthread_mutex_unlock(&philo->data->mutex);
}

