/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dieandra <dieandra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:00:00 by dieandra          #+#    #+#             */
/*   Updated: 2026/07/28 16:00:00 by dieandra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_tokens(char const *s, char c)
{
	int	tokens;
	int	i;

	i = 0;
	tokens = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			tokens++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (tokens);
}

static char	*alloc_word(char const *s, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static void	*free_split(char **v_ptr, int i)
{
	while (i > 0)
		free(v_ptr[--i]);
	free(v_ptr);
	return (NULL);
}

static char	**fill_split(char **v_ptr, char const *s, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			v_ptr[j++] = alloc_word(s, start, i);
			if (!v_ptr[j - 1])
				return (free_split(v_ptr, j - 1));
		}
	}
	v_ptr[j] = NULL;
	return (v_ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**v_ptr;

	if (!s)
		return (NULL);
	v_ptr = malloc(sizeof(char *) * (count_tokens(s, c) + 1));
	if (!v_ptr)
		return (NULL);
	return (fill_split(v_ptr, s, c));
}
