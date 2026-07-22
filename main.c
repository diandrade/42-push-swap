#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack *stack_a;
	t_stack *stack_b;
	int disorder;

	if (argc < 2)
		return (0);

	stack_a = NULL;
	stack_b = NULL;

	stack_init(argc, argv, &stack_a);
	stack_assign_index(stack_a);

	disorder = stack_disorder(stack_a);

	stack_print(stack_a);

	if (!stack_is_sorted(stack_a))
	{
		if (stack_size(stack_a) <= 5)
			sort_small(&stack_a, &stack_b);
		else
			sort_chunks(&stack_a, &stack_b);
	}

	stack_print(stack_a);

	stack_free(&stack_a);
	stack_free(&stack_b);
	return (0);
}
