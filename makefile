CC = cc
CFLAGS = -Werror -Wextra -Wall -g3 #-fsanitize=address
RM = rm -rf
UTILS_FILES = ./utils/ft_split.c ./utils/ft_memmove.c ./utils/ft_strncmp.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_strdup.c ./utils/char_in_cmd.c
EXEC_FILES =  ./execution/execution.c execution/check_paths.c ./execution/exiter.c ./execution/builtins/builtins.c ./execution/builtins/env.c ./execution/builtins/pwd.c ./execution/builtins/cd.c ./execution/builtins/echo.c
PARSING_FILES = ./parsing/mini_parsing.c ./parsing/redirectors.c
CFILES = main.c ${EXEC_FILES} ${PARSING_FILES} ${UTILS_FILES}
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
