/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcde-c <marcde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:00:00 by dieandra          #+#    #+#             */
/*   Updated: 2026/07/28 15:00:36 by marcde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_log(t_strategy *opt, int *counter, char *name)
{
	(*counter)++;
	opt->total_ops++;
	if (opt->count_only)
		return ;
	ft_putstr_fd(name, 1);
}
