/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:12:06 by alfsanch          #+#    #+#             */
/*   Updated: 2024/09/21 17:23:00 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Returns 1 if it is a letter of the abcd of ASCII
*/
int	ft_isalpha(int letter)
{
	if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
	{
		return (1);
	}
	else
		return (0);
}

/*int main(void)
{
	char c1 = 'A';
	char c2 = '2';
	printf("ft_isalpha('%c') = %d\n", c1, ft_isalpha(c1));
	printf("ft_isalpha('%c') = %d\n", c2, ft_isalpha(c2));
}*/