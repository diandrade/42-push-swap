#include "push_swap.h"

int main(int argc, char *argv[])
{
    int  i;
    t_stack *stack_a;

    i = 1;
    stack_a = ft_lstnew(ft_atoi(argv[i++]));

    if (argc > 2)
    {
        while (i < argc)
        {
            ft_lstadd_back(&stack_a, ft_lstnew(ft_atoi(argv[i])));
            i++;
        }
    }
    print_stack(stack_a);
}