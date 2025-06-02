/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:25:18 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/09 19:25:22 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Concatenates s1 and s2 in a new memory space + the null char at the end
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	newstr;
	char	*s3;

	i = 0;
	j = 0;
	newstr = ft_strlen(s1) + ft_strlen(s2);
	s3 = malloc(newstr +1);
	if (s3 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}

/*int main(void)
{
    char *str1 = "Hola, ";
    char *str2 = "mundo!";
    char *result = ft_strjoin(str1, str2);
	printf("Cadena unida: %s\n", result);
}*/