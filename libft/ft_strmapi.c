/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:23:24 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/09 19:23:27 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Traverses s and applies the function we pass it. Create new string
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *)malloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
char	conversor(unsigned int none, char c)
{
	char	a;
	a = (int)(c + none);
	return (a);
}
int	main(void)
{
	char	stringc [] = "Hola Mundo";
	printf("%s\n",stringc);
	printf("%s\n",ft_strmapi(stringc, conversor));
}
*/