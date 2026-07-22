/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_radix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcde-c <marcde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 18:05:09 by marcde-c          #+#    #+#             */
/*   Updated: 2026/07/22 18:05:42 by marcde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_bits(int size)
{
	int	bits;
	int	max_index;

	bits = 0;
	max_index = size - 1;
	while (max_index > 0)
	{
		bits++;
		max_index >>= 1;
	}
	return (bits);
}

static void	radix_pass(t_stack **a, t_stack **b, int bit, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (((*a)->index >> bit) & 1)
			ra(a, 1);
		else
			pb(a, b);
		i++;
	}
	while (*b != NULL)
		pa(a, b);
}

void	sort_complex(t_stack **a, t_stack **b)
{
	int	size;
	int	bits;
	int	bit;

	size = stack_size(*a);
	if (size <= 1 || stack_is_sorted(*a))
		return ;
	stack_assign_index(*a);
	bits = count_bits(size);
	bit = 0;
	while (bit < bits)
	{
		radix_pass(a, b, bit, size);
		bit++;
	}
}
