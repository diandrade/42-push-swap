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

static void sort_three(t_stack **a)
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
        rra(a, 1);
        sa(a, 1);
    }
    else if (v1 < v0 && v0 < v2)
        sa(a, 1);
    else if (v2 < v0 && v0 < v1)
        rra(a, 1);
    else if (v1 < v2 && v2 < v0)
        ra(a, 1);
    else
    {
        sa(a, 1);
        rra(a, 1);
    }
}

static void sort_generic_small(t_stack **a, t_stack **b)
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
                ra(a, 1);
        }
        else
        {
            while (min_idx++ < size)
                rra(a, 1);
        }
        pb(a, b);
    }
    sort_three(a);
    while (*b)
        pa(a, b);
}

void    sort_small(t_stack **a, t_stack **b)
{
    int size;

    size = stack_size(*a);
    if (size <= 1)
        return ;
    if (size == 2)
    {
        if ((*a)->content > (*a)->next->content)
            sa(a, 1);
        return ;
    }
    if (size == 3)
        sort_three(a);
    else
        sort_generic_small(a, b);
}