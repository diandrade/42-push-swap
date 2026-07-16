#include "push_swap.h"

void *parser(char *arg)
{
    size_t  i;

    i = 0;
    while (arg[i])
    {
        if (!isdigit(arg[i]))
        {
            return NULL;
        }
        i++;
    }
    return (ft_atoi(arg));
}