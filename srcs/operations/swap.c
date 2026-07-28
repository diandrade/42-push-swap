/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dieandra <dieandra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:00:00 by dieandra          #+#    #+#             */
/*   Updated: 2026/07/28 16:00:00 by dieandra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stack **a, int print, t_strategy *opt)
{
	t_stack	*first;
	t_stack	*second;

	if (*a == NULL || (*a)->next == NULL)
		return ;
	first = *a;
	second = (*a)->next;
	first->next = second->next;
	second->next = first;
	*a = second;
	if (print)
		op_log(opt, &opt->sa, "sa\n");
}

void	sb(t_stack **b, int print, t_strategy *opt)
{
	t_stack	*first;
	t_stack	*second;

	if (*b == NULL || (*b)->next == NULL)
		return ;
	first = *b;
	second = (*b)->next;
	first->next = second->next;
	second->next = first;
	*b = second;
	if (print)
		op_log(opt, &opt->sb, "sb\n");
}

void	ss(t_stack **a, t_stack **b, int print, t_strategy *opt)
{
	sa(a, 0, opt);
	sb(b, 0, opt);
	if (print)
		op_log(opt, &opt->ss, "ss\n");
}
