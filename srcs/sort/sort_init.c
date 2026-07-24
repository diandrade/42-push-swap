#include "push_swap.h"

void    sort_init(t_strategy *opt)
{
    opt->is_bench = 0;
	opt->sort_mode = "adaptative";
    opt->disorder_pct = 0;
    opt->sa = 0; opt->sb = 0; opt->ss = 0;
    opt->pa = 0; opt->pb = 0;
    opt->ra = 0; opt->rb = 0; opt->rr = 0;
    opt->rra = 0; opt->rrb = 0; opt->rrr = 0;
    opt->total_ops = 0;
}