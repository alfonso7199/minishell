/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:26:12 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/09 19:26:15 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Reserves a block of memory to an array of n elements each of 
size and normally filling it with 0
*/
void	*ft_calloc(size_t n, size_t size)
{
	char	*str;

	if (n <= 0 || size <= 0)
		str = (char *)malloc(1);
	else
		str = (char *)malloc(n * size);
	if (!str)
		return (NULL);
	return (ft_memset(str, 0, n * size));
}

/*int main()
{
	size_t n = 5;
	size_t size = sizeof(int);

	int *array = (int *)ft_calloc(n, size);
	int i = 0;
	while (i < n)
	{
		printf("array %d\n", array[i]);
		i++:
	}
}*/