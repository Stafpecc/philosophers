/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:51:57 by tarini            #+#    #+#             */
/*   Updated: 2025/03/26 14:47:36 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

static void	ft_bzero(void *s, size_t n)
{
	size_t	count;

	count = -1;
	while (++count < n)
		((char *)s)[count] = 0;
}

static void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*ptr;
	size_t	product;

	if (elementCount == 0 || elementSize == 0)
		return (malloc(0));
	if (elementCount > SIZE_MAX / elementSize)
		return (NULL);
	product = elementCount * elementSize;
	ptr = malloc(product);
	if (!ptr)
		return (ptr);
	ft_bzero(ptr, product);
	return (ptr);
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

static void	ft_sign(char *str, unsigned int *num, size_t *start, int n)
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
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_sign(str, &num, &start, n);
	while (len > start)
	{
		str[len - 1] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	return (str);
}
