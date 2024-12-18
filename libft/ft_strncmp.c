/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <yourail@student.ausanne.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:21:46 by kaykin            #+#    #+#             */
/*   Updated: 2024/01/18 14:22:14 by kaykin           ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*word1;
	unsigned char	*word2;

	word1 = (unsigned char *)s1;
	word2 = (unsigned char *)s2;
	i = 0;
	while (i < n && *word1 != '\0' && *word2 != '\0')
	{
		if (*word1 != *word2)
		{
			return (*word1 - *word2);
		}
		word1++;
		word2++;
		i++;
	}
	if (i == n)
	{
		return (0);
	}
	else
	{
		return (*word1 - *word2);
	}
}
