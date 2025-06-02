/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:51:47 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/14 17:19:16 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Find the 1st occurrence of byte c in the first n bytes of *s
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	i;

	i = 0;
	d = (unsigned char *) s;
	while (i < n)
	{
		if (d[i] == (unsigned char)c)
		{
			return ((void *)(d + i));
		}
		i++;
	}
	return (NULL);
}

/*int main(void) {
    const char str[] = "Hello, World!";
    char ch = 'W';
    size_t n = sizeof(str);

    char *result = ft_memchr(str, ch, n);
    printf("ft_memchr: El carácter '%c' encontrado 
	en la posición: %ld\n", ch, result - str);
}*/