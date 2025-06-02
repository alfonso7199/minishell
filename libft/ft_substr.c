/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:25:46 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/09 19:25:48 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Returns a new string with size len and which is cut off s from
 where indicated by start
*/
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		return (ft_strdup(""));
	}
	if (len > s_len)
		len = s_len;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}

// int main(void) {
//     const char *str = "123456";
//     unsigned int start = 5;
//     size_t len = 5;
// 	char *substr = ft_substr(str, start, len);
//     printf("Subcadena desde índice %u: '%s'\n", start, substr);
// }