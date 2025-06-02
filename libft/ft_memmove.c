/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:28:58 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/14 17:26:11 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Copies n bytes from src to dst, but unlike memcpy
handles data copying in case memory areas overlap.
*/
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*tmp;
	char	*dest;

	tmp = (char *)src;
	dest = (char *)dst;
	if (tmp < dest)
	{
		while (n--)
			dest[n] = tmp[n];
	}
	else
		ft_memcpy(dest, tmp, n);
	return (dst);
}

/*int main(void)
{
    char str1[] = "Hola Mundo";
    char str2[20];
    ft_memmove(str2, str1, strlen(str1) + 1);
    printf("str2 después de ft_memmove: %s\n", str2);
}*/