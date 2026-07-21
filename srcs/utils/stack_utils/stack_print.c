#include "push_swap.h"

void	stack_print(t_stack *head)
{
	t_stack	*current;

	current = head;
	while (current != NULL)
	{
		ft_putstr("[");
		ft_putnbr_long(current->content);
		ft_putstr("]");
		if (current->next != NULL)
			ft_putstr(" -> ");
		current = current->next;
	}
	write(1, "\n", 1);
}