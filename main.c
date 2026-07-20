#include "push_swap.h"

int	check_numbers(char **dst)
{
	int	i;
	int	j;

	if (!dst || !dst[0])
		return (0);
	i = 0;
	while (dst[i] != NULL)
	{
		j = 0;
		if (dst[i][j] == '-' || dst[i][j] == '+')
			j++;
		if (!dst[i][j])
			return (0);
		while (dst[i][j])
		{
			if (ft_isdigit(dst[i][j]))
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

char	**parse_args(int argc, char **argv)
{
	static int	i;
	char		**dst;

	if (!i)
		i = 1;
	dst = NULL;
	if (i < argc)
	{
		dst = ft_split(argv[i++], ' ');
		if (check_numbers(dst))
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

		while ((current_args = parse_args(argc, argv)) != NULL)
		{
			i = 0;
			while (current_args[i] != NULL)
			{
				pa(current_args[i], &stack_a);
				i++;
			}
		}

		print_stack(stack_a);
		return (0);
	}
	return (1);
}