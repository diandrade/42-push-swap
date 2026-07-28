/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dieandra <dieandra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:00:00 by dieandra          #+#    #+#             */
/*   Updated: 2026/07/28 16:00:00 by dieandra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_stack **a, int print, t_strategy *opt)
{
	t_stack	*first;
	t_stack	*last;

	if (*a == NULL || (*a)->next == NULL)
		return ;
	first = *a;
	*a = first->next;
	last = *a;
	while (last->next != NULL)
		last = last->next;
	last->next = first;
	first->next = NULL;
	if (print)
		op_log(opt, &opt->ra, "ra\n");
}

void	rb(t_stack **b, int print, t_strategy *opt)
{
	t_stack	*first;
	t_stack	*last;

	if (*b == NULL || (*b)->next == NULL)
		return ;
	first = *b;
	*b = first->next;
	last = *b;
	while (last->next != NULL)
		last = last->next;
	last->next = first;
	first->next = NULL;
	if (print)
		op_log(opt, &opt->rb, "rb\n");
}

void	rr(t_stack **a, t_stack **b, int print, t_strategy *opt)
{
	ra(a, 0, opt);
	rb(b, 0, opt);
	if (print)
		op_log(opt, &opt->rr, "rr\n");
}
