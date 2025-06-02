/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:05:16 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/14 17:18:20 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Converts the first n bytes of *s to zero
*/

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*b;

	b = (unsigned char *) s;
	while (n != 0)
	{
		*b = '\0';
		b++;
		n--;
	}
}

/*int main()
{
	char str[10] = "Hola Mundo";
	size_t n = 5;
	ft_bzero(str, n);
	int i = 0;
	while(i <= 10)
	{
		if (str[i] == '\0')
			printf("\\0");
		else
			printf("%c",str[i])
		i++;
	}
}*/