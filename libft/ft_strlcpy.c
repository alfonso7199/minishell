/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:29:34 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/09 19:29:37 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Copies one string to another making sure there is space.
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	size_t			src_len;

	i = 0;
	if (src == NULL)
		return (0);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (i < size - 1 && i < src_len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

/*int main(void)
{
    char dest[20];
    const char *src = "Hola, mundo!"; 
    size_t size = sizeof(dest); 
    size_t result = ft_strlcpy(dest, src, size);
    printf("Cadena copiada: %s\n", dest);
    printf("Longitud de la fuente: %zu\n", result);
}*/