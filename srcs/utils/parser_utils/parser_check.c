#include "push_swap.h"

int	parser_check_format(char **dst)
{
	int	i;

	if (!dst || !dst[0])
		return (0);
	i = 0;
	while (dst[i] != NULL)
	{
		if (!ft_isnumber(dst[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parser_check_dup_and_limits(t_stack *stack_a, char **dst)
{
	int		i;
	long	char_to_int;

	i = 0;
	while (dst[i] != NULL)
	{
		char_to_int = ft_atol(dst[i]);
		if (ft_lstfind(stack_a, char_to_int) || char_to_int > INT_MAX
			|| char_to_int < INT_MIN)
		{
			return (0);
		}
		i++;
	}
	return (1);
}