#include "push_swap.h"


void    stack_init(int argc, char **argv, t_stack *stack_a)
{
    char **current_args;
    int i;

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
}
