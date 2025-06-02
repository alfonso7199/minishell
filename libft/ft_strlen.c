/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:52:36 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/09 16:50:17 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

/*int main(void)
{
    const char *my_string = "Hola, mundo!";
    size_t length = ft_strlen(my_string);
    printf("La longitud de la cadena \"%s\" es: %zu\n", my_string, length);
}*/