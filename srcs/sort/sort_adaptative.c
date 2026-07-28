#include "push_swap.h"

void	sort_adaptative(double disorder, t_stack **stack_a, t_stack **stack_b,
		t_strategy *opt)
{
	if (disorder < 20)
		sort_small(stack_a, stack_b, opt);
	else if (disorder < 50)
		sort_chunk(stack_a, stack_b, opt);
	else
		sort_radix(stack_a, stack_b, opt);
}