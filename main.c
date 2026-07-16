#include "push_swap.h"

int main(int argc, char **argv)
{
    int  i;
    t_stack *stack_a;
    char **splitted_args;

    splitted_args = NULL;
    if (argc > 2)
    {
        i = 0;
        while(argv[i++])
        {
            splitted_args = ft_split(argv[i], ' ');
        }
    }

    i = 0;
    while(!ft_isdigit(splitted_args[i++]))
    {
        return 0;
    }

    append_node(splitted_args, &stack_a);
    print_stack(stack_a);
}