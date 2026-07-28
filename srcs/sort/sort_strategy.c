#include "push_swap.h"

void	sort_strategy(double disorder, t_stack **stack_a, t_stack **stack_b,
		t_strategy *opt)
{
	if (ft_strncmp(opt->sort_mode, "adaptive", 9) == 0)
		sort_adaptative(disorder, stack_a, stack_b, opt);
	else if (ft_strncmp(opt->sort_mode, "simple", 7) == 0)
		sort_small(stack_a, stack_b, opt);
	else if (ft_strncmp(opt->sort_mode, "medium", 7) == 0)
		sort_chunk(stack_a, stack_b, opt);
	else
		sort_radix(stack_a, stack_b, opt);
}