#include "push_swap.h"

void    pa(char *content, t_stack **stack_a)
{
	ft_lstadd_back(stack_a, ft_lstnew(ft_atoi(content)));
}
    