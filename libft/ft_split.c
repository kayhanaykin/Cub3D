/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:52:10 by kaykin            #+#    #+#             */
/*   Updated: 2023/12/18 18:01:57 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_word_count(char const *s, char c);
static char		**ft_array_fill(char const *s, char c,
					char **word_array, int j);
static int		ft_free_arrays(char **word_array, int *j);

char	**ft_split(char const *s, char c)
{
	char			**word_array;
	int				j;

	word_array = (char **)malloc ((ft_word_count (s, c) + 1) * sizeof(char *));
	if (word_array == NULL)
		return (NULL);
	j = 0;
	return (ft_array_fill (s, c, word_array, j));
}

static size_t	ft_word_count(char const *s, char c)
{
	size_t	i;
	size_t	word_count;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			word_count++;
			while (s[i] != c)
			{
				if (i == ft_strlen(s) - 1)
					return (word_count);
				i++;
			}
		}
		i++;
	}
	return (word_count);
}

static char	**ft_array_fill(char const *s, char c, char **word_array, int j)
{
	size_t			i;
	unsigned int	start;

	i = 0;
	start = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || (s[i - 1] == c)))
		{
			start = i;
		}
		if (s[i] != c && (i == (ft_strlen (s) - 1) || s[i + 1] == c))
		{
			word_array[j] = ft_substr (s, start, (i - start + 1));
			if (ft_free_arrays(word_array, &j))
			{
				return (word_array);
			}
		}
		i++;
	}
	word_array[j] = NULL;
	return (word_array);
}

static int	ft_free_arrays(char **word_array, int *j)
{
	if (word_array[*j] == NULL)
	{
		(*j)--;
		while (*j >= 0)
		{
			free (word_array[(*j)--]);
		}
		free (word_array);
		return (1);
	}
	(*j)++;
	return (0);
}
