/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:45:22 by alfsanch          #+#    #+#             */
/*   Updated: 2024/09/21 17:49:21 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
If it is a number
*/
int	ft_isdigit(int digit)
{
	if (digit >= '0' && digit <= '9')
		return (1);
	else
		return (0);
}

/*int main(void)
{
    int char1 = '5';
    int char2 = 'a';
    printf("ft_isdigit('%c') = %d\n", char1, ft_isdigit(char1));
    printf("ft_isdigit('%c') = %d\n", char2, ft_isdigit(char2));
}*/