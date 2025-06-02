/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:31:29 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/14 17:03:37 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Find the last occurrence of c in str
*/
char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		i--;
	}
	return (0);
}

/*int main(void)
{
    const char *str = "Hola Mundo, ¿cómo estás?";
    char c1 = 'o';
    char *result1 = ft_strrchr(str, c1);
    if (result1)
        printf("Encontrado '%c': '%s'\n", c1, result1);
    else
        printf("No encontrado: '%c'\n", c1);
}*/