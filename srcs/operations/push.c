/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dieandra <dieandra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:00:00 by dieandra          #+#    #+#             */
/*   Updated: 2026/07/28 16:00:00 by dieandra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_stack **a, t_stack **b, t_strategy *opt)
{
	t_stack	*moved;

	if (*b == NULL)
		return ;
	moved = *b;
	*b = (*b)->next;
	moved->next = *a;
	*a = moved;
	op_log(opt, &opt->pa, "pa\n");
}

void	pb(t_stack **a, t_stack **b, t_strategy *opt)
{
	t_stack	*moved;

	if (*a == NULL)
		return ;
	moved = *a;
	*a = (*a)->next;
	moved->next = *b;
	*b = moved;
	op_log(opt, &opt->pb, "pb\n");
}
