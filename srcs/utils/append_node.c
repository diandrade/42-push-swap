#include "push_swap.h"

void    append_node(t_stack **stack_a, long content)
{
	ft_lstadd_back(stack_a, ft_lstnew(content));
}
    