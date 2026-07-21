#include "push_swap.h"

t_stack	*ft_lstnew(long content)
{
	t_stack	*dst;

	dst = malloc(sizeof(t_stack));
	if (!dst)
		return (NULL);
	dst->content = content;
	dst->next = NULL;
	return (dst);
}