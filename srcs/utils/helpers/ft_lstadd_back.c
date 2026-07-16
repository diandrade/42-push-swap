#include "push_swap.h"

void	ft_lstadd_back(t_stack **lst, t_stack *new)
{
	t_stack	*last_node;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last_node = ft_lstlast(*lst);
		last_node->next = new;
	}
}