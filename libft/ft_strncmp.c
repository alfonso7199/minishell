/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:23:17 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/13 13:26:22 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Compares two strings up to n
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	int				j;
	unsigned char	*s11;
	unsigned char	*s22;

	i = 0;
	j = 0;
	s11 = (unsigned char *) s1;
	s22 = (unsigned char *) s2;
	while ((s11[i] != '\0') && (s22[j] != '\0') && (n != '\0'))
	{
		if ((s11[i] != s22[j]))
			return (s11[i] - s22[j]);
		i++;
		j++;
		n--;
	}
	if (n == 0)
		return (0);
	return (s11[i] - s22[j]);
}

/*int main(void)
{
    const char *str1 = "Hola";
    const char *str2 = "Hola Mundo";
    int result1 = ft_strncmp(str1, str2, 4);
    printf("Comparando '%s' y '%s': %d\n", str1, str2, result1);
}*/