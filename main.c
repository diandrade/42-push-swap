#include "push_swap.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_format(char **dst)
{
	int	i;

	if (!dst || !dst[0])
		return (0);
	i = 0;
	while (dst[i] != NULL)
	{
		if (!is_valid_number(dst[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_duplicates_and_limits(t_stack *stack_a, char **dst)
{
	int	i;
	long char_to_int;

	i = 0;
	while (dst[i] != NULL)
	{
		char_to_int = ft_atol(dst[i]);

		if (ft_lstfind(stack_a, char_to_int) || char_to_int > INT_MAX || char_to_int < INT_MIN)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

char	**parse_args(int argc, char **argv, t_stack *stack_a)
{
	static int	i;
	char		**dst;

	if (!i)
		i = 1;
	dst = NULL;
	if (i < argc)
	{
		dst = ft_split(argv[i++], ' ');
		if (check_format(dst) && check_duplicates_and_limits(stack_a, dst))
			return (dst);
		write(2, "Error\n", 6);
		exit(1);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_stack *stack_a;
	char **current_args;
	int i;

	if (argc > 1)
	{
		stack_a = NULL;

		while ((current_args = parse_args(argc, argv, stack_a)) != NULL)
		{
			i = 0;
			while (current_args[i] != NULL)
			{
				append_node(&stack_a, ft_atol(current_args[i]));
				i++;
			}
		}

		print_stack(stack_a);
		return (0);
	}
	return (1);
}