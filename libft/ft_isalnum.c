/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:52:26 by alfsanch          #+#    #+#             */
/*   Updated: 2024/09/21 17:57:23 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Returns 1 if it is an alphanumeric char (alphabet or number) of ASCII
*/
int	ft_isalnum(int alnum)
{
	if ((alnum >= 'a' && alnum <= 'z' ) || (alnum >= 'A' && alnum <= 'Z')
		|| (alnum >= '0' && alnum <= '9'))
		return (1);
	else
		return (0);
}

/*int main(void)
{
    char c1 = '5';  
    char c2 = '!';  
	printf("ft_isalnum('%c') = %d\n", c1, ft_isalnum(c1));
    printf("ft_isalnum('%c') = %d\n", c2, ft_isalnum(c2));
}*/