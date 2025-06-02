/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:01:14 by alfsanch          #+#    #+#             */
/*   Updated: 2024/09/21 18:02:20 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
If it is a valid ASCII char
*/
int	ft_isascii(int ascii)
{
	if (ascii >= 0 && ascii <= 127)
		return (1);
	else
		return (0);
}

/*int main(void)
{
    int char1 = 127;
    int char2 = 128;
    printf("ft_isascii('%c') = %d\n", char1, ft_isascii(char1));
    printf("ft_isascii('%c') = %d\n", char2, ft_isascii(char2));
}*/