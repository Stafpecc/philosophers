/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:53:28 by tarini            #+#    #+#             */
/*   Updated: 2025/03/27 16:43:27 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	ret_error(int *error)
{
	*error = 1;
	return (1);
}

int	ft_atoi(const char *str, int *error)
{
	long	result;
	int		sign;

	*error = 0;
	result = 0;
	sign = 1;
	*error = 0;
	while (*str >= '0' && *str <= '9')
	{
		if ((result > ((INT_MAX - (*str - '0')) / 10) && sign == 1) || (result
				> (((long)INT_MAX + 1 - (*str - '0')) / 10) && sign == -1))
			return (ret_error(error));
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (ret_error(error));
	result *= sign;
	if (result > INT_MAX || result < (-INT_MAX - 1))
		return (ret_error(error));
	return ((int)result);
}
