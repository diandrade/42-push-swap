/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_radix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcde-c <marcde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:00:00 by dieandra          #+#    #+#             */
/*   Updated: 2026/07/28 15:01:27 by marcde-c         ###   ########.fr       */
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

static void	radix_pass(t_stack **a, t_stack **b, int bit, t_strategy *opt)
{
	int	i;
	int	size;

	i = 0;
	size = stack_size(*a);
	while (i < size)
	{
		if (((*a)->index >> bit) & 1)
			ra(a, 1, opt);
		else
			pb(a, b, opt);
		i++;
	}
	while (*b != NULL)
		pa(a, b, opt);
}

void	sort_radix(t_stack **a, t_stack **b, t_strategy *opt)
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
		radix_pass(a, b, bit, opt);
		bit++;
	}
}
