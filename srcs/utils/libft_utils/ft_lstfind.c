#include "push_swap.h"

int	ft_lstfind(t_stack *stack, long value)
{
	while (stack != NULL)
	{
		if (stack->content == value)
			return (1);
		stack = stack->next;
	}
	return (0);
}