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

	sort_init(&opt);
	stack_init(argc, argv, &stack_a, &opt);
	stack_assign_index(stack_a);
	disorder = stack_disorder(stack_a);

	if (!stack_is_sorted(stack_a))
	{
		sort_strategy(disorder, &stack_a, &stack_b, &opt);
	}

	printf("\n=== DEBUG BENCHMARK ===\n");
	printf("is_bench: %d\n", opt.is_bench);
	printf("sort_mode: %s\n", opt.sort_mode);
	printf("disorder: %d%%\n", disorder);
	printf("total_ops: %d\n", opt.total_ops);
	printf("sa: %d | sb: %d | ss: %d\n", opt.sa, opt.sb, opt.ss);
	printf("pa: %d | pb: %d\n", opt.pa, opt.pb);
	printf("ra: %d | rb: %d | rr: %d\n", opt.ra, opt.rb, opt.rr);
	printf("rra: %d | rrb: %d | rrr: %d\n", opt.rra, opt.rrb, opt.rrr);
	printf("=======================\n\n");

	stack_free(&stack_a);
	stack_free(&stack_b);
	return (0);
}