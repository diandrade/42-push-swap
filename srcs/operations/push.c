#include "push_swap.h"

void    pa(t_stack **a, t_stack **b, t_strategy *opt)
{
    t_stack *moved;

    if (*b == NULL)
        return ;
    moved = *b;
    *b = (*b)->next;
    moved->next = *a;
    *a = moved;
    if (opt)
    {
        opt->pa++;
        opt->total_ops++;
    }
    write(1, "pa\n", 3);
}

void    pb(t_stack **a, t_stack **b, t_strategy *opt)
{
    t_stack *moved;

    if (*a == NULL)
        return ;
    moved = *a;
    *a = (*a)->next;
    moved->next = *b;
    *b = moved;
    if (opt)
    {
        opt->pb++;
        opt->total_ops++;
    }
    write(1, "pb\n", 3);
}