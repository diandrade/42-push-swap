#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack *stack_a;
	t_stack *stack_b;
	t_strategy opt;
	int disorder;

	if (argc < 2)
		return (0);

	stack_a = NULL;
	stack_b = NULL;

	opt.is_bench = 0;
	opt.sort_mode = "adaptative";

	stack_init(argc, argv, &stack_a, &opt);
	stack_assign_index(stack_a);
	disorder = stack_disorder(stack_a);

	if (!stack_is_sorted(stack_a))
	{
		sort_strategy(disorder, &stack_a, &stack_b, &opt);
	}

	stack_free(&stack_a);
	stack_free(&stack_b);
	return (0);
}