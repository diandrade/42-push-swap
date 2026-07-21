#include "push_swap.h"

static void	sort_three(t_stack **a)
{
	int	v0;
	int	v1;
	int	v2;

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

void	sort_small(t_stack **a, t_stack **b)
{
	int	size;

	(void)b;
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
}