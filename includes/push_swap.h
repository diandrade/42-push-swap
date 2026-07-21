#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* Libraries */
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

/* Structs */
typedef struct s_stack
{
	long			content;
	struct s_stack	*next;
}	t_stack;

/* Methods */
	/* Helpers*/
		char	**ft_split(char const *s, char c);
		void	ft_lstadd_back(t_stack **lst, t_stack *new);
		long	ft_atol(const char *str);
		int	ft_lstfind(t_stack *stack, long value);
		int	ft_isdigit(int c);
		size_t	ft_strlen(const char *s);
		t_stack	*ft_lstnew(long content);
		t_stack *ft_lstlast(t_stack *lst);
		
	/* Utils */
		void    print_stack(t_stack *head);
		void    append_node(t_stack **stack_a, long content);

	/* Operations */
		void	pa(t_stack **a, t_stack **b);
		void	pb(t_stack **a, t_stack **b);
		void	sa(t_stack **a, int print);
		void	sb(t_stack **b, int print);
		void	ss(t_stack **a, t_stack **b, int print);
		void	ra(t_stack **a, int print);
		void	rb(t_stack **b, int print);
		void	rr(t_stack **a, t_stack **b, int print);
		void	rra(t_stack **a, int print);
		void	rrb(t_stack **b, int print);
		void	rrr(t_stack **a, t_stack **b, int print);

#endif