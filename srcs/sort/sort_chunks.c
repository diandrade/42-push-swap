#include "push_swap.h"

static int	get_chunk_size(int size)
{
	if (size <= 20)
		return (4);
	if (size <= 100)
		return (15);
	return (32);
}

static void	push_chunks(t_stack **a, t_stack **b, int chunk_size)
{
	int	start;
	int	end;

	start = 0;
	end = chunk_size;
	while (*a != NULL)
	{
		if ((*a)->index < end)
		{
			pb(a, b);
			if ((*b)->index < start + (chunk_size / 2))
				rb(b, 1);
			start++;
			end++;
		}
		else
			ra(a, 1);
	}
}

static int	find_max_position(t_stack *b)
{
	int		i;
	int		pos;
	int		max;
	t_stack	*curr;

	if (b == NULL)
		return (0);
	i = 0;
	pos = 0;
	curr = b;
	max = curr->index;
	while (curr != NULL)
	{
		if (curr->index > max)
		{
			max = curr->index;
			pos = i;
		}
		curr = curr->next;
		i++;
	}
	return (pos);
}

static void	rotate_to_top(t_stack **b, int pos)
{
	int	size;
	int	rotations;

	size = stack_size(*b);
	if (pos <= size / 2)
	{
		rotations = pos;
		while (rotations-- > 0)
			rb(b, 1);
	}
	else
	{
		rotations = size - pos;
		while (rotations-- > 0)
			rrb(b, 1);
	}
}

void	sort_chunks(t_stack **a, t_stack **b)
{
	int size;
	int chunk_size;

	size = stack_size(*a);
	if (size <= 3)
	{
		sort_small(a, b);
		return ;
	}

	stack_assign_index(*a);
	chunk_size = get_chunk_size(size);
	push_chunks(a, b, chunk_size);

	while (*b != NULL)
	{
		rotate_to_top(b, find_max_position(*b));
		pa(a, b);
	}
}