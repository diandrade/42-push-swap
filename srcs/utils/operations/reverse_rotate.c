#include "push_swap.h"

void	rra(t_stack **a, int print)
{
	t_stack	*second_last;
	t_stack	*last;

	if (*a == NULL || (*a)->next == NULL)
		return ;
	second_last = *a;
	while (second_last->next->next != NULL)
		second_last = second_last->next;
	last = second_last->next;
	second_last->next = NULL;
	last->next = *a;
	*a = last;
	if (print)
		write(1, "rra\n", 4);
}

void	rrb(t_stack **b, int print)
{
	t_stack	*second_last;
	t_stack	*last;

	if (*b == NULL || (*b)->next == NULL)
		return ;
	second_last = *b;
	while (second_last->next->next != NULL)
		second_last = second_last->next;
	last = second_last->next;
	second_last->next = NULL;
	last->next = *b;
	*b = last;
	if (print)
		write(1, "rrb\n", 4);
}

void	rrr(t_stack **a, t_stack **b, int print)
{
	rra(a, 0);
	rrb(b, 0);
	if (print)
		write(1, "rrr\n", 4);
}