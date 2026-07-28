/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcde-c <marcde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:02:16 by marcde-c          #+#    #+#             */
/*   Updated: 2026/07/28 15:02:20 by marcde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_print(t_stack *head)
{
	t_stack	*current;

	current = head;
	while (current != NULL)
	{
		ft_putstr_fd("[", 1);
		ft_putnbr_long_fd(current->content, 1);
		ft_putstr_fd("]", 1);
		if (current->next != NULL)
			ft_putstr_fd(" -> ", 1);
		current = current->next;
	}
	write(1, "\n", 1);
}
