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

typedef struct s_flags
{
	int				is_bench;
	char			*sort_mode;
}					t_flags;

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
void				ft_putstr(char *str);
void				ft_putnbr_long(long n);

/* Parser Utils */
char				**parser_parse_args(int argc, char **argv, t_stack *stack_a,
						t_flags *opt);
int					parser_check_fmt_and_flags(char **dst, t_flags *opt);
int					parser_check_dup_and_limits(t_stack *stack_a, char **dst);
void				parser_free(char **arr);

/* Stack Utils */
int					stack_is_sorted(t_stack *stack);
void				stack_print(t_stack *head);
void				stack_append(t_stack **stack_a, long content);
int					stack_size(t_stack *stack);
void				stack_assign_index(t_stack *stack_a);
void				stack_free(t_stack **stack);
int					stack_disorder(t_stack *stack_a);
void				stack_init(int argc, char **argv, t_stack **stack_a,
						t_flags *opt);

/* Sort Strategies */
void				sort_small(t_stack **a, t_stack **b);
void				sort_chunk(t_stack **a, t_stack **b);
void				sort_radix(t_stack **a, t_stack **b);
void				sort_adaptative(int disorder, t_stack **stack_a,
						t_stack **stack_b);
void				sort_strategy(int disorder, t_stack **stack_a,
						t_stack **stack_b, t_flags *opt);

/* Operations */
void				pa(t_stack **a, t_stack **b);
void				pb(t_stack **a, t_stack **b);
void				sa(t_stack **a, int print);
void				sb(t_stack **b, int print);
void				ss(t_stack **a, t_stack **b, int print);
void				ra(t_stack **a, int print);
void				rb(t_stack **b, int print);
void				rr(t_stack **a, t_stack **b, int print);
void				rra(t_stack **a, int print);
void				rrb(t_stack **b, int print);
void				rrr(t_stack **a, t_stack **b, int print);

#endif