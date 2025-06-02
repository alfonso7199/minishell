/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:22:46 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/09 19:22:48 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Traverses s and applies the function we tell it to each char in the string
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

/*
void	upper(unsigned int i, char *string1)
{
	string1[i] = ft_toupper(string1[i]);
}
int main(void)
{
    char str[] = "hola, mundo!";
	ft_striteri(str, upper);
    printf("Cadena modificada: ");
    printf("\n");
}*/