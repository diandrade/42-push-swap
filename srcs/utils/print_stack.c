#include "push_swap.h"

void    print_stack(t_stack *head)
{
    t_stack *current = head;
    while (current != NULL)
    {
        printf("[%ld]", current -> content);
        if (current -> next != NULL)
            printf(" -> ");
        current = current -> next;
    }
    printf("\n");
}