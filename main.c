#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack *stack_a;
	t_stack *stack_b;
	char **current_args;
	int i;

	if (argc < 2)
		return (0);

	stack_a = NULL;
	stack_b = NULL;

	while ((current_args = parser_parse_args(argc, argv, stack_a)) != NULL)
	{
		i = 0;
		while (current_args[i] != NULL)
		{
			stack_append(&stack_a, ft_atol(current_args[i]));
			i++;
		}
		parser_free(current_args);
	}

	if (!stack_is_sorted(stack_a))
	{
		if (stack_size(stack_a) <= 5)
			sort_small(&stack_a, &stack_b);
		else
			sort_chunks(&stack_a, &stack_b);
	}

	stack_free(&stack_a);
	stack_free(&stack_b);
	return (0);
}