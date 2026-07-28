/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dieandra <dieandra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:00:00 by dieandra          #+#    #+#             */
/*   Updated: 2026/07/28 16:00:00 by dieandra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_stack **a, int print, t_strategy *opt)
{
	t_stack	*last;
	t_stack	*second_last;

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
		op_log(opt, &opt->rra, "rra\n");
}

void	rrb(t_stack **b, int print, t_strategy *opt)
{
	t_stack	*last;
	t_stack	*second_last;

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
		op_log(opt, &opt->rrb, "rrb\n");
}

void	rrr(t_stack **a, t_stack **b, int print, t_strategy *opt)
{
	rra(a, 0, opt);
	rrb(b, 0, opt);
	if (print)
		op_log(opt, &opt->rrr, "rrr\n");
}
