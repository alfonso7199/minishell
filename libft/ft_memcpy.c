/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:51:47 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/14 17:17:42 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Copies n bytes from str_origin to str_dest.
*/
void	*ft_memcpy(void *str_dest, const void *str_origen, size_t n)
{
	unsigned char		*destino;
	const unsigned char	*origen;
	size_t				i;

	destino = (unsigned char *) str_dest;
	origen = (const unsigned char *) str_origen;
	i = 0;
	if (!destino && !origen)
		return (NULL);
	while (i < n)
	{
		destino[i] = origen[i];
		i++;
	}
	return (str_dest);
}

/*int main(void) 
{
    char source[] = "Hello, World!";
    char destination[20];
    size_t n = 13;
    ft_memcpy(destination, source, n);
    destination[n] = '\0';
}*/