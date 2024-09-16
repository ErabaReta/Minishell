CC = cc
CFLAGS = -Werror -Wextra -Wall -g3 #-fsanitize=address
RM = rm -rf
GARBAGE_MAKER= ./garbage_collector/fail_protect.c garbage_collector/heap_controller.c garbage_collector/fd_pool.c
UTILS_FILES = ./utils/ft_split.c ./utils/ft_memmove.c ./utils/ft_strncmp.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_strdup.c ./utils/char_in_cmd.c ./utils/ft_substr.c ./utils/ft_lst_op.c ./utils/ft_tabledup.c ./utils/ft_tablejoin.c ./utils/ft_isalnum.c ./utils/print_err.c ./utils/ft_itoa.c ./utils/ft_atoi.c ./utils/ft_isdigit.c ./utils/ft_iswhitespace.c ./utils/includes_space.c ./utils/ft_strchr.c ./utils/sort_table.c
EXEC_FILES =  ./execution/execution.c execution/check_paths.c  ./execution/builtins/builtins.c ./execution/builtins/ft_env.c ./execution/builtins/ft_pwd.c ./execution/builtins/ft_cd.c ./execution/builtins/ft_echo.c ./execution/builtins/ft_unset.c ./execution/builtins/ft_export.c ./execution/redirect.c ./execution/builtins/ft_exit.c ./execution/exec_signals.c
PARSING_FILES = ./parsing/lexer.c ./parsing/syntax_error.c ./parsing/ft_expand.c ./parsing/ft_quotes.c ./parsing/ft_redirection.c ./parsing/catch_expand.c ./parsing/sig_handler.c ./execution/exiter.c ./parsing/expand_vars.c
ENV= ./env/env.c ./env/env_helper.c ./env/init_env.c ./env/slice_var_value.c
CFILES = main.c  ${PARSING_FILES} ${UTILS_FILES} ${GARBAGE_MAKER} ${ENV} ${EXEC_FILES}
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

################# TODO remember to remove this ######################
run : all
	valgrind --suppressions=readline.supp --leak-check=full --track-fds=yes ./minishell

rerun : re run clean
#####################################################################