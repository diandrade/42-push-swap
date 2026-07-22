#include "push_swap.h"

int	stack_disorder(t_stack *stack_a)
{
	t_stack *i;
	t_stack *j;
	int mistakes;
	int total_pairs;

	if (!stack_a || !stack_a->next)
		return (0);
	mistakes = 0;
	total_pairs = 0;
	i = stack_a;
	while (i != NULL)
	{
		j = i->next;
		while (j != NULL)
		{
			if (i->content > j->content)
				mistakes++;
			total_pairs++;
			j = j->next;
		}
		i = i->next;
	}

	return ((mistakes * 100) / total_pairs);
}