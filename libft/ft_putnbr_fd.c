/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:20:27 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/09 19:20:31 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Write an int nbr in the fd
*/
void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	temp;

	temp = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		temp = (unsigned int)(n * -1);
	}
	if (temp > 9)
		ft_putnbr_fd(temp / 10, fd);
	ft_putchar_fd((char)(temp % 10 + '0'), fd);
}

/*int main (void)
{
	ft_putnbr_fd(12345, STDOUT_FILENO);
    ft_putchar_fd('\n', STDOUT_FILENO); 
}*/