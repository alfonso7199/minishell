/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:24:18 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/09 19:24:21 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
Splits the string into substrings when it encounters char c
*/
static int	ft_count(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_fill_array(char **aux, char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		k;
	size_t	s_len;

	i = 0;
	k = 0;
	s_len = ft_strlen(s);
	while (s[i])
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		j = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (j >= s_len)
			aux[k++] = "\0";
		else
			aux[k++] = ft_substr(s, j, i - j);
	}
	return (aux);
}

char	**ft_split(char const *s, char c)
{
	char	**aux;
	int		num_words;

	if (!s)
		return (NULL);
	num_words = ft_count(s, c);
	aux = malloc((num_words + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	aux = ft_fill_array(aux, s, c);
	aux[num_words] = NULL;
	return (aux);
}

/*int main(void)
{
    char **result;
    char *s = "Hola, mundo que tal";
    char c = ' ';
    int i = 0;
    result = ft_split(s, c);
    printf("Las palabras separadas son:\n");
    while (result[i])
    {
        printf("%s\n", result[i]);
        i++;
    }
}*/