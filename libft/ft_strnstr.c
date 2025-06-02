/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:39:17 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/14 17:39:22 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Searches for big in little but limited to len bytes.
*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	a;
	size_t	little_len;
	size_t	b;

	a = 0;
	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	while (big[a] != '\0' && a < len)
	{
		b = 0;
		while (big[a + b] == little[b] && a + b < len)
		{
			if (little[b + 1] == '\0')
				return ((char *)&big[a]);
			b++;
		}
		a++;
	}
	return (NULL);
}

/*int main(void)
{
    const char *big = "Hola, bienvenido al mundo de la programación!";
    const char *little1 = "bienvenido";
    size_t len = 30; 
    char *result1 = ft_strnstr(big, little1, len);
    if (result1)
        printf("Encontrado: '%s'\n", result1);
    else
        printf("No encontrado: '%s'\n", little1);
}*/