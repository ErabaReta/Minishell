CC = cc
CFLAGS = -Wall -Wextra -Werror
CFILS = main.c\
				allocator.c\
				allocator_op.c
OFILS = $(CFILS:.c=.o)
NAME = minishell

all : $(NAME)

$(NAME): $(OFILS)
	$(CC) $(OFILS) -lreadline -o $(NAME)
%.o: %.c
	$(CC) -c $< -o $@
clean:
	rm -rf $(OFILS)
fclean: clean
	rm -rf $(NAME)
re : fclean all
