CC = cc
CFLAGS = -Werror -Wextra -Wall -g
RM = rm -rf
CFILES = main.c #get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c
OFILES = ${CFILES:.c=.o}
NAME = minishell

# INCLUDES = -I. -I./get_next_line/

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