#include "push_swap.h"

void    pa(t_stack **stack_a, long content)
{
	ft_lstadd_back(stack_a, ft_lstnew(content));
}
    