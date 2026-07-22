CC = cc

CFLAGS = -Wall -Wextra -Werror -g -I./includes

RM = rm -rf

NAME = push_swap

SRCS =  main.c \
        srcs/sort/sort_small.c \
        srcs/sort/sort_chunks.c \
        srcs/operations/push.c \
        srcs/operations/reverse_rotate.c \
        srcs/operations/rotate.c \
        srcs/operations/swap.c \
        srcs/utils/parser_utils/parser_check.c \
        srcs/utils/parser_utils/parser_parse_args.c \
        srcs/utils/parser_utils/parser_free.c \
        srcs/utils/stack_utils/stack_append.c \
        srcs/utils/stack_utils/stack_assign_index.c \
        srcs/utils/stack_utils/stack_free.c \
        srcs/utils/stack_utils/stack_is_sorted.c \
        srcs/utils/stack_utils/stack_print.c \
        srcs/utils/stack_utils/stack_size.c \
        srcs/utils/libft_utils/ft_atol.c \
        srcs/utils/libft_utils/ft_isdigit.c \
        srcs/utils/libft_utils/ft_isnumber.c \
        srcs/utils/libft_utils/ft_lstadd_back.c \
        srcs/utils/libft_utils/ft_lstfind.c \
        srcs/utils/libft_utils/ft_lstlast.c \
        srcs/utils/libft_utils/ft_lstnew.c \
        srcs/utils/libft_utils/ft_putnbr_long.c \
        srcs/utils/libft_utils/ft_putstr.c \
        srcs/utils/libft_utils/ft_split.c \
        srcs/utils/libft_utils/ft_strlen.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: all
	./$(NAME)

.PHONY: all clean fclean re