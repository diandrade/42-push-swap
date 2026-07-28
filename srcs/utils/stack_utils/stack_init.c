/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dieandra <dieandra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:00:00 by dieandra          #+#    #+#             */
/*   Updated: 2026/07/28 16:00:00 by dieandra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	append_tokens(char **args, t_stack **stack_a)
{
	int	j;

	j = 0;
	while (args[j] != NULL)
	{
		if (!parser_is_flag(args[j]))
			stack_append(stack_a, ft_atol(args[j]));
		j++;
	}
}

void	stack_init(int argc, char **argv, t_stack **stack_a, t_strategy *opt)
{
	char	**args;
	int		i;

	i = 1;
	while (i < argc)
	{
		args = parser_parse_args(argv[i], *stack_a, opt);
		append_tokens(args, stack_a);
		parser_free(args);
		i++;
	}
}
