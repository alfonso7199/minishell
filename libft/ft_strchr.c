/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:31:03 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/14 17:08:55 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Searches for c in *str and returns a pointer to the position
 where it is found for the first time.
*/
char	*ft_strchr(const char *str, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*str)
	{
		if (*str == uc)
			return ((char *)str);
		str++;
	}
	if (uc == '\0')
		return ((char *)str);
	return (0);
}

/*int main(void){
	const char *str = "Hola Mundo que tal";
	int c = 'M';
	char *resultado = ft_strchr(str, c);
	printf("Cadena a partir del carcter : %s", resultado);
}*/