/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dieandra <dieandra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:00:00 by dieandra          #+#    #+#             */
/*   Updated: 2026/07/28 16:00:00 by dieandra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	parser_is_flag(char *str)
{
	if (ft_strncmp(str, "--bench", 8) == 0)
		return (1);
	if (ft_strncmp(str, "--simple", 9) == 0)
		return (1);
	if (ft_strncmp(str, "--medium", 9) == 0)
		return (1);
	if (ft_strncmp(str, "--complex", 10) == 0)
		return (1);
	if (ft_strncmp(str, "--adaptive", 11) == 0)
		return (1);
	return (0);
}

int	parser_check_fmt_and_flags(char **dst, t_strategy *opt)
{
	int	i;

	if (!dst || !dst[0])
		return (0);
	i = 0;
	while (dst[i] != NULL)
	{
		if (ft_strncmp(dst[i], "--bench", 8) == 0)
			opt->is_bench = 1;
		else if (ft_strncmp(dst[i], "--simple", 9) == 0)
			opt->sort_mode = "simple";
		else if (ft_strncmp(dst[i], "--medium", 9) == 0)
			opt->sort_mode = "medium";
		else if (ft_strncmp(dst[i], "--complex", 10) == 0)
			opt->sort_mode = "complex";
		else if (ft_strncmp(dst[i], "--adaptive", 11) == 0)
			opt->sort_mode = "adaptive";
		else if (!ft_isnumber(dst[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** Duplicatas dentro do MESMO argumento (ex.: ./push_swap "1 2 2") nao
** aparecem na stack ainda, porque a stack so e preenchida depois da
** validacao. Por isso comparamos tambem com os tokens anteriores de dst.
*/
static int	is_dup_in_dst(char **dst, int limit, long value)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		if (!parser_is_flag(dst[i]) && ft_atol(dst[i]) == value)
			return (1);
		i++;
	}
	return (0);
}

int	parser_check_dup_and_limits(t_stack *stack_a, char **dst)
{
	int		i;
	long	char_to_int;

	i = 0;
	while (dst[i] != NULL)
	{
		if (parser_is_flag(dst[i]))
		{
			i++;
			continue ;
		}
		char_to_int = ft_atol(dst[i]);
		if (char_to_int > INT_MAX || char_to_int < INT_MIN)
			return (0);
		if (ft_lstfind(stack_a, char_to_int) || is_dup_in_dst(dst, i,
				char_to_int))
			return (0);
		i++;
	}
	return (1);
}
