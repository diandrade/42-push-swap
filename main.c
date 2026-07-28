/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dieandra <dieandra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:00:00 by dieandra          #+#    #+#             */
/*   Updated: 2026/07/28 16:00:00 by dieandra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	t_strategy	opt;
	double		disorder;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	sort_init(&opt);
	stack_init(argc, argv, &stack_a, &opt);
	stack_assign_index(stack_a);
	disorder = stack_disorder(stack_a);
	opt.disorder_pct = disorder;
	if (!stack_is_sorted(stack_a))
		sort_strategy(disorder, &stack_a, &stack_b, &opt);
	if (opt.is_bench == 1)
		sort_print_bench(&opt);
	stack_free(&stack_a);
	stack_free(&stack_b);
	return (0);
}
