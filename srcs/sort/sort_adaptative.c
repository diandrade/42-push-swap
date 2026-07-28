/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_adaptative.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcde-c <marcde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 14:17:35 by marcde-c          #+#    #+#             */
/*   Updated: 2026/07/28 14:17:38 by marcde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_adaptative(double disorder, t_stack **stack_a, t_stack **stack_b,
		t_strategy *opt)
{
	if (stack_size(*stack_a) <= 5)
	{
		sort_small(stack_a, stack_b, opt);
		return ;
	}
	if (disorder < 0.2)
		sort_small(stack_a, stack_b, opt);
	else if (disorder < 0.5)
		sort_chunk(stack_a, stack_b, opt);
	else
		sort_radix(stack_a, stack_b, opt);
}
