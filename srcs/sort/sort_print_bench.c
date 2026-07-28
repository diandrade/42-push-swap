#include "push_swap.h"

static void	print_strategy_name(t_strategy *opt)
{
	ft_putstr_fd("[bench] strategy: ", 2);
	if (ft_strncmp(opt->sort_mode, "simple", 7) == 0)
		ft_putstr_fd("Simple / O(n^2)\n", 2);
	else if (ft_strncmp(opt->sort_mode, "medium", 7) == 0)
		ft_putstr_fd("Medium / O(n\\sqrt{n})\n", 2);
	else if (ft_strncmp(opt->sort_mode, "complex", 7) == 0)
		ft_putstr_fd("Complex / O(n log n)\n", 2);
	else if (ft_strncmp(opt->sort_mode, "adaptive", 7) == 0)
	{
		ft_putstr_fd("Adaptive / ", 2);
		if (opt->disorder_pct < 0.20)
			ft_putstr_fd("O(n^2)\n", 2);
		else if (opt->disorder_pct < 0.50)
			ft_putstr_fd("O(n\\sqrt{n})\n", 2);
		else
			ft_putstr_fd("O(n log n)\n", 2);
	}
}

static void	print_ops_details(t_strategy *opt)
{
	ft_putstr_fd("[bench] sa: ", 2);
	ft_putnbr_long_fd(opt->sa, 2);
	ft_putstr_fd(" sb: ", 2);
	ft_putnbr_long_fd(opt->sb, 2);
	ft_putstr_fd(" ss: ", 2);
	ft_putnbr_long_fd(opt->ss, 2);
	ft_putstr_fd(" pa: ", 2);
	ft_putnbr_long_fd(opt->pa, 2);
	ft_putstr_fd(" pb: ", 2);
	ft_putnbr_long_fd(opt->pb, 2);
	ft_putstr_fd("\n[bench] ra: ", 2);
	ft_putnbr_long_fd(opt->ra, 2);
	ft_putstr_fd(" rb: ", 2);
	ft_putnbr_long_fd(opt->rb, 2);
	ft_putstr_fd(" rr: ", 2);
	ft_putnbr_long_fd(opt->rr, 2);
	ft_putstr_fd(" rra: ", 2);
	ft_putnbr_long_fd(opt->rra, 2);
	ft_putstr_fd(" rrb: ", 2);
	ft_putnbr_long_fd(opt->rrb, 2);
	ft_putstr_fd(" rrr: ", 2);
	ft_putnbr_long_fd(opt->rrr, 2);
	ft_putstr_fd("\n", 2);
}

void	sort_print_bench(t_strategy *opt)
{
	if (!opt || !opt->is_bench)
		return ;
	ft_putstr_fd("[bench] disorder: ", 2);
	ft_putdouble_fd(opt->disorder_pct, 2, 2);
	ft_putstr_fd("%\n", 2);
	print_strategy_name(opt);
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_long_fd(opt->total_ops, 2);
	ft_putstr_fd("\n", 2);
	print_ops_details(opt);
}