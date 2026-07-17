CC = cc

CFLAGS = -Wall -Wextra -Werror -g -I./includes

RM = rm -rf

NAME = push_swap

SRCS =  srcs/utils/helpers/ft_lstadd_back.c \
		srcs/utils/helpers/ft_lstlast.c \
		srcs/utils/helpers/ft_lstnew.c \
		srcs/utils/helpers/ft_split.c \
		srcs/utils/helpers/ft_strjoin.c \
		srcs/utils/helpers/ft_strlen.c \
		srcs/utils/helpers/ft_atoi.c \
		srcs/utils/helpers/ft_isdigit.c \
		srcs/utils/print_stack.c \
		srcs/utils/append_node.c \
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