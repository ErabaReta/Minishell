CC = cc
CFLAGS = -Werror -Wextra -Wall
RM = rm -rf
CFILES = main.c
OFILES = ${CFILES:.c=.o}
NAME = minishell

all : ${NAME}

${NAME} : ${OFILES}
	${CC} ${CFLAGS} ${OFILES} -o ${NAME}

.o.c :
	${CC} ${CFLAGS} -c $< -o $@

clean :
	${RM} ${OFILES}

fclean : clean
	${RM} ${NAME}

re : fclean all