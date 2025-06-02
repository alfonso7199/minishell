/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:26:37 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/14 17:04:40 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
copy s into a new memory area
*/
char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	s2 = malloc(len + 1);
	if (s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

/*int main(void)
{
    char *original = "Hola, mundo!";
    char *duplicada;
    duplicada = ft_strdup(original);
    printf("Cadena original: %s\n", original);
	printf("Cadena duplicada: %s\n", duplicada);
}*/