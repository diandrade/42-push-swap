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
	int			content;
	struct s_stack	*next;
}	t_stack;

/* Methods */
	/* Helpers*/
		char	**ft_split(char const *s, char c);
		char	*ft_strjoin(char const *s1, char const *s2);
		void	ft_lstadd_back(t_stack **lst, t_stack *new);
		size_t	ft_strlen(const char *s);
		t_stack	*ft_lstnew(int content);
		t_stack *ft_lstlast(t_stack *lst);
		int	ft_isdigit(int c);
		int	ft_atoi(const char *nptr);
		
	/* Utils */
		void    print_stack(t_stack *head);
		void    append_node(char **args, t_stack **stack);
#endif