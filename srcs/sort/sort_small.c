#include "push_swap.h"

static int  find_min_index(t_stack *a)
{
    int     min_val;
    int     min_idx;
    int     i;
    t_stack *curr;

    min_val = a->content;
    min_idx = 0;
    i = 0;
    curr = a;
    while (curr)
    {
        if (curr->content < min_val)
        {
            min_val = curr->content;
            min_idx = i;
        }
        curr = curr->next;
        i++;
    }
    return (min_idx);
}

static void sort_three(t_stack **a, t_strategy *opt)
{
    int v0;
    int v1;
    int v2;

    v0 = (*a)->content;
    v1 = (*a)->next->content;
    v2 = (*a)->next->next->content;
    if (v0 < v1 && v1 < v2)
        return ;
    else if (v0 < v2 && v2 < v1)
    {
        rra(a, 1, opt);
        sa(a, 1, opt);
    }
    else if (v1 < v0 && v0 < v2)
        sa(a, 1, opt);
    else if (v2 < v0 && v0 < v1)
        rra(a, 1, opt);
    else if (v1 < v2 && v2 < v0)
        ra(a, 1, opt);
    else
    {
        sa(a, 1, opt);
        rra(a, 1, opt);
    }
}

static void sort_generic_small(t_stack **a, t_stack **b, t_strategy *opt)
{
    int min_idx;
    int size;

    while (stack_size(*a) > 3)
    {
        min_idx = find_min_index(*a);
        size = stack_size(*a);
        if (min_idx <= size / 2)
        {
            while (min_idx-- > 0)
                ra(a, 1, opt);
        }
        else
        {
            while (min_idx++ < size)
                rra(a, 1, opt);
        }
        pb(a, b, opt);
    }
    sort_three(a, opt);
    while (*b)
        pa(a, b, opt);
}

void    sort_small(t_stack **a, t_stack **b, t_strategy *opt)
{
    int size;

    size = stack_size(*a);
    if (size <= 1)
        return ;
    if (size == 2)
    {
        if ((*a)->content > (*a)->next->content)
            sa(a, 1, opt);
        return ;
    }
    if (size == 3)
        sort_three(a, opt);
    else
        sort_generic_small(a, b, opt);
}