/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:09:07 by alfsanch          #+#    #+#             */
/*   Updated: 2024/09/21 18:10:37 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
If it is an ASCII printable character
*/
int	ft_isprint(int c)
{
	if ((c > 31) && (c < 127))
		return (1);
	else
		return (0);
}

/*int main(void)
{
    int char1 = '~';
    int char2 = 31;
    printf("ft_isprint('%c') = %d\n", char1, ft_isprint(char1));
    printf("ft_isprint('%c') = %d\n", char2, ft_isprint(char2));
}*/