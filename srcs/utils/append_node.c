#include "push_swap.h"

void    append_node(char **args, t_stack *stack)
{
    int i;

    i = 0;
    stack = ft_lstnew(ft_atoi(args[i]));
    while (i < ft_arglen(args))
    {
        ft_lstadd_back(&stack, ft_lstnew(ft_atoi(args[i])));
        i++;
    }
}