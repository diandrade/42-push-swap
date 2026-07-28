#include "push_swap.h"

void	stack_init(int argc, char **argv, t_stack **stack_a, t_strategy *opt)
{
	char	**current_args;
	int		i;

	while ((current_args = parser_parse_args(argc, argv, *stack_a, opt)) != NULL)
	{
		i = 0;
		while (current_args[i] != NULL)
		{
			if (!parser_is_flag(current_args[i]))
				stack_append(stack_a, ft_atol(current_args[i]));
			i++;
		}
		parser_free(current_args);
	}
}