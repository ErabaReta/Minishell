CC = cc
CFLAGS = -Werror -Wextra -Wall
RM = rm -rf
CFILES = main.c ./execution/execution.c ./execution/ft_split.c ./execution/ft_memmove.c #get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c
OFILES = ${CFILES:.c=.o}
NAME = minishell

INCLUDES = -I. -I./get_next_line/ -I./execution/

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