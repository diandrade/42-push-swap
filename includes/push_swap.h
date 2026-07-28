#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* Libraries */
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* Structs */
typedef struct s_stack
{
	long			content;
	int				index;
	struct s_stack	*next;
}					t_stack;

typedef struct s_strategy
{
	int				is_bench;
	char			*sort_mode;
	double			disorder_pct;
	int				sa;
	int				sb;
	int				ss;
	int				pa;
	int				pb;
	int				ra;
	int				rb;
	int				rr;
	int				rra;
	int				rrb;
	int				rrr;
	int				total_ops;
}					t_strategy;

/* Libft Utils */
char				**ft_split(char const *s, char c);
void				ft_lstadd_back(t_stack **lst, t_stack *new);
long				ft_atol(const char *str);
int					ft_lstfind(t_stack *stack, long value);
int					ft_isdigit(int c);
int					ft_isnumber(char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlen(const char *s);
t_stack				*ft_lstnew(long content);
t_stack				*ft_lstlast(t_stack *lst);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_long_fd(long n, int fd);
void				ft_putdouble_fd(double n, int precision, int fd);

/* Parser Utils */
char				**parser_parse_args(int argc, char **argv, t_stack *stack_a,
						t_strategy *opt);
int					parser_check_fmt_and_flags(char **dst, t_strategy *opt);
int					parser_check_dup_and_limits(t_stack *stack_a, char **dst);
void				parser_free(char **arr);

/* Stack Utils */
int					stack_is_sorted(t_stack *stack);
void				stack_print(t_stack *head);
void				stack_append(t_stack **stack_a, long content);
int					stack_size(t_stack *stack);
void				stack_assign_index(t_stack *stack_a);
void				stack_free(t_stack **stack);
double				stack_disorder(t_stack *stack_a);
void				stack_init(int argc, char **argv, t_stack **stack_a,
						t_strategy *opt);

/* Sort Strategies */
void				sort_init(t_strategy *opt);
void				sort_print_bench(t_strategy *opt);
void				sort_small(t_stack **a, t_stack **b, t_strategy *opt);
void				sort_chunk(t_stack **a, t_stack **b, t_strategy *opt);
void				sort_radix(t_stack **a, t_stack **b, t_strategy *opt);
void				sort_adaptative(double disorder, t_stack **stack_a,
						t_stack **stack_b, t_strategy *opt);
void				sort_strategy(double disorder, t_stack **stack_a,
						t_stack **stack_b, t_strategy *opt);

/* Operations */
void				pa(t_stack **a, t_stack **b, t_strategy *opt);
void				pb(t_stack **a, t_stack **b, t_strategy *opt);
void				sa(t_stack **a, int print, t_strategy *opt);
void				sb(t_stack **b, int print, t_strategy *opt);
void				ss(t_stack **a, t_stack **b, int print, t_strategy *opt);
void				ra(t_stack **a, int print, t_strategy *opt);
void				rb(t_stack **b, int print, t_strategy *opt);
void				rr(t_stack **a, t_stack **b, int print, t_strategy *opt);
void				rra(t_stack **a, int print, t_strategy *opt);
void				rrb(t_stack **b, int print, t_strategy *opt);
void				rrr(t_stack **a, t_stack **b, int print, t_strategy *opt);

#endif