CC = cc

CFLAGS = -Wall -Wextra -Werror -g -I./includes

RM = rm -rf

NAME = push_swap

SRCS =  srcs/utils/helpers/ft_lstadd_back.c \
		srcs/utils/helpers/ft_lstfind.c \
		srcs/utils/helpers/ft_lstlast.c \
		srcs/utils/helpers/ft_lstnew.c \
		srcs/utils/helpers/ft_split.c \
		srcs/utils/helpers/ft_strlen.c \
		srcs/utils/helpers/ft_atol.c \
		srcs/utils/helpers/ft_isdigit.c \
		srcs/utils/operations/push.c \
		srcs/utils/operations/reverse_rotate.c \
		srcs/utils/operations/rotate.c \
		srcs/utils/operations/swap.c \
		srcs/utils/append_node.c \
		srcs/utils/print_stack.c \
		main.c \

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