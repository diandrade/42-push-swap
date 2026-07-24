#include "push_swap.h"

void    ra(t_stack **a, int print, t_strategy *opt)
{
    t_stack *first;
    t_stack *last;

    if (*a == NULL || (*a)->next == NULL)
        return ;
    first = *a;
    *a = first->next;
    last = *a;
    while (last->next != NULL)
        last = last->next;
    last->next = first;
    first->next = NULL;
    if (print)
    {
        if (opt)
        {
            opt->ra++;
            opt->total_ops++;
        }
        write(1, "ra\n", 3);
    }
}

void    rb(t_stack **b, int print, t_strategy *opt)
{
    t_stack *first;
    t_stack *last;

    if (*b == NULL || (*b)->next == NULL)
        return ;
    first = *b;
    *b = first->next;
    last = *b;
    while (last->next != NULL)
        last = last->next;
    last->next = first;
    first->next = NULL;
    if (print)
    {
        if (opt)
        {
            opt->rb++;
            opt->total_ops++;
        }
        write(1, "rb\n", 3);
    }
}

void    rr(t_stack **a, t_stack **b, int print, t_strategy *opt)
{
    ra(a, 0, opt);
    rb(b, 0, opt);
    if (print)
    {
        if (opt)
        {
            opt->rr++;
            opt->total_ops++;
        }
        write(1, "rr\n", 3);
    }
}