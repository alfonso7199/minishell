/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:30:10 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/09 19:30:12 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Concatenates src to dst making sure it does not exceed size.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest;
	size_t	source;
	size_t	size_dst;

	dest = ft_strlen(dst);
	size_dst = ft_strlen(dst);
	source = 0;
	if (size <= size_dst)
		return (ft_strlen(src) + size);
	while (size_dst < size - 1 && src[source] != '\0')
	{
		dst[size_dst] = src[source];
		size_dst++;
		source++;
	}
	dst[size_dst] = '\0';
	return (ft_strlen(src) + dest);
}

/*int main(void)
{
    char dest[50] = "Hola, "; 
    char *src = "mundo!";
    size_t size = sizeof(dest); 
    size_t result = ft_strlcat(dest, src, size);
    printf("Cadena resultante: %s\n", dest);
    printf("Longitud total: %zu\n", result);
}*/