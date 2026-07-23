#include "push_swap.h"

void	sort_adaptative(int disorder, t_stack **stack_a, t_stack **stack_b)
{
	if (disorder < 20)
		sort_small(stack_a, stack_b);
	else if (disorder < 50)
		sort_chunk(stack_a, stack_b);
	else
		sort_radix(stack_a, stack_b);
}
