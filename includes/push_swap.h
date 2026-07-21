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
		size_t	ft_strlen(const char *s);
		long	ft_atol(const char *str);
		t_stack	*ft_lstnew(long content);
		t_stack *ft_lstlast(t_stack *lst);
		int	ft_lstfind(t_stack *stack, long value);
		int	ft_isdigit(int c);
		
		
	/* Utils */
		void    print_stack(t_stack *head);
		void    append_node(t_stack **stack_a, long content);

#endif