#include "push_swap.h"

void    pa(t_stack **stack_a, int content)
{
	ft_lstadd_back(stack_a, ft_lstnew(content));
}
    