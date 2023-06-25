NAME			=	minishell
CFLAGS			=	-Wall -Wextra -Werror
CC				=	gcc
MAKE			=	make

READLINE_DIR	=	readline
LIBFT_DIR		=	libft

HEADERS			=	minishell.h var_list/var_list.h cmd_list/cmd_list.h parsing/parse.h cmd_exec/cmd_exec.h builtin/builtin.h
INCLUDE			=	-I . -I var_list -I cmd_list -I parsing -I cmd_exec -I builtin -I libft -I $(READLINE_DIR)
LIB_DIRS		=	-L $(LIBFT_DIR) -L $(READLINE_DIR)
SRCS			=	minishell.c minishell_utils.c \
					var_list/var_list.c var_list/var_list_fn.c var_list/var_list_utils.c \
					cmd_list/cmd_list.c cmd_list/split_input.c cmd_list/split_input_utils.c cmd_list/cmd_argv.c cmd_list/cmd_argv_utils.c \
					cmd_list/expansion.c cmd_list/expansion_utils.c\
					parsing/parse.c \
					cmd_exec/cmd_exec.c cmd_exec/cmd_exec_utils.c cmd_exec/run.c cmd_exec/run_utils.c \
					cmd_exec/redirect.c cmd_exec/redirect_utils.c cmd_exec/heredoc.c \
					builtin/builtin.c builtin/cd.c builtin/pwd.c builtin/env.c \
					builtin/export.c builtin/export_utils.c builtin/unset.c builtin/echo.c builtin/exit.c

OBJS			=	$(patsubst %.c,%.o,$(SRCS))

all : $(NAME)

$(NAME): $(OBJS) libft readline
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_DIRS) -lft -lhistory -lreadline -ltermcap

%.o : %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

libft:
	cd $(LIBFT_DIR) && $(MAKE)

readline:

clean :
	rm -f $(OBJS)
	cd $(LIBFT_DIR) && $(MAKE) clean

fclean : clean
	rm -f $(NAME)
	cd $(LIBFT_DIR) && $(MAKE) fclean

re : fclean all

.PHONY : all clean fclean re libft readline
