#include "push_swap.h"

static void	parser_fatal_error(char **dst, t_stack *stack_a)
{
	t_stack	*next;

	parser_free(dst);
	while (stack_a)
	{
		next = stack_a->next;
		free(stack_a);
		stack_a = next;
	}
	write(2, "Error\n", 6);
	exit(1);
}

char	**parser_parse_args(int argc, char **argv, t_stack *stack_a, t_strategy *opt)
{
	static int	i;
	char		**dst;

	if (!i)
		i = 1;
	dst = NULL;
	if (i < argc)
	{
		dst = ft_split(argv[i++], ' ');
		if (parser_check_fmt_and_flags(dst, opt)
			&& parser_check_dup_and_limits(stack_a, dst))
			return (dst);
		parser_fatal_error(dst, stack_a);
	}
	return (NULL);
}