/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_disorder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcde-c <marcde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:00:00 by dieandra          #+#    #+#             */
/*   Updated: 2026/07/28 15:04:54 by marcde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double	stack_disorder(t_stack *stack_a)
{
	t_stack	*i;
	t_stack	*j;
	double	mistakes;
	double	total_pairs;

	if (!stack_a || !stack_a->next)
		return (0.0);
	mistakes = 0;
	total_pairs = 0;
	i = stack_a;
	while (i != NULL)
	{
		j = i->next;
		while (j != NULL)
		{
			if (i->content > j->content)
				mistakes++;
			total_pairs++;
			j = j->next;
		}
		i = i->next;
	}
	return (mistakes / total_pairs);
}
