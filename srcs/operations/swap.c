#include "push_swap.h"

void    sa(t_stack **a, int print, t_strategy *opt)
{
    t_stack *first;
    t_stack *second;

    if (*a == NULL || (*a)->next == NULL)
        return ;
    first = *a;
    second = (*a)->next;
    first->next = second->next;
    second->next = first;
    *a = second;
    if (print)
    {
        if (opt)
        {
            opt->sa++;
            opt->total_ops++;
        }
        write(1, "sa\n", 3);
    }
}

void    sb(t_stack **b, int print, t_strategy *opt)
{
    t_stack *first;
    t_stack *second;

    if (*b == NULL || (*b)->next == NULL)
        return ;
    first = *b;
    second = (*b)->next;
    first->next = second->next;
    second->next = first;
    *b = second;
    if (print)
    {
        if (opt)
        {
            opt->sb++;
            opt->total_ops++;
        }
        write(1, "sb\n", 3);
    }
}

void    ss(t_stack **a, t_stack **b, int print, t_strategy *opt)
{
    sa(a, 0, opt);
    sb(b, 0, opt);
    if (print)
    {
        if (opt)
        {
            opt->ss++;
            opt->total_ops++;
        }
        write(1, "ss\n", 3);
    }
}