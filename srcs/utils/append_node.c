#include "push_swap.h"

void    append_node(char **args, t_stack **stack)
{
    int i;
    t_stack *new_node;

    if (!args || !args[0])
        return;

    i = 0;
    while (args[i])
    {
        new_node = ft_lstnew(ft_atoi(args[i]));
        ft_lstadd_back(stack, new_node);
        i++;
    }
}