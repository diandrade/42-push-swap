#include "push_swap.h"

void	stack_assign_index(t_stack *stack_a)
{
	t_stack	*current;
	t_stack	*compare;
	int		index;

	current = stack_a;
	while (current != NULL)
	{
		index = 0;
		compare = stack_a;
		while (compare != NULL)
		{
			if (compare->content < current->content)
				index++;
			compare = compare->next;
		}
		current->index = index;
		current = current->next;
	}
}