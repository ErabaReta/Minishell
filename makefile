CC = cc
CFLAGS = -Werror -Wextra -Wall #-g3 -fsanitize=address
RM = rm -rf
CFILES = main.c ./execution/execution.c ./utils/ft_split.c ./utils/ft_memmove.c ./utils/ft_strncmp.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_strdup.c #get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c
OFILES = ${CFILES:.c=.o}
NAME = minishell

# INCLUDES = -I. -I./get_next_line/ -I./execution/

all : ${NAME}

${NAME} : ${OFILES}
	${CC} ${CFLAGS} ${OFILES} -lreadline -o ${NAME}

%.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

clean :
	${RM} ${OFILES}

fclean : clean
	${RM} ${NAME}

re : fclean all
