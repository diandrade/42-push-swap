#include "push_swap.h"

int parser_check_fmt_and_flags(char **dst, t_flags *opt)
{
    int i;

    if (!dst || !dst[0])
        return (0);
    i = 0;
    while (dst[i] != NULL)
    {
        if (ft_strncmp(dst[i], "--bench", 8) == 0)
            opt->is_bench = 1;
        if (ft_strncmp(dst[i], "--simple", 9) == 0)
            opt->sort_mode = "simple";
        if (ft_strncmp(dst[i], "--medium", 9) == 0)
            opt->sort_mode = "medium";
        if (ft_strncmp(dst[i], "--complex", 10) == 0)
            opt->sort_mode = "complex";
        if (ft_strncmp(dst[i], "--adaptative", 13) == 0)
            opt->sort_mode = "adaptative";
        if (!ft_isnumber(dst[i]))
            return (0);
        i++;
    }
    return (1);
}

int	parser_check_dup_and_limits(t_stack *stack_a, char **dst)
{
	int i;
	long char_to_int;

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