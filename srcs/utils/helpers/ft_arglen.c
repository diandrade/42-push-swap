#include "push_swap.h"

int ft_arglen(char  **args)
{
    int     i;

    i = 0;
    while (args[i] != NULL)
    {
        i++;
    }

    return i;
}