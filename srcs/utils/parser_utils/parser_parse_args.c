#include "push_swap.h"

char	**parser_parse_args(int argc, char **argv, t_stack *stack_a, t_flags *opt)
{
	static int	i;
	char		**dst;

	if (!i)
		i = 1;
	dst = NULL;
	if (i < argc)
	{
		dst = ft_split(argv[i++], ' ');
		if (parser_check_fmt_and_flags(dst, opt) && parser_check_dup_and_limits(stack_a, dst))
			return (dst);
		write(2, "Error\n", 6);
		exit(1);
	}
	return (NULL);
}