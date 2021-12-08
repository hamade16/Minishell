NAME	= minishell

SRCS	= main.c \
		parse/parse_expand_utils_two.c parse/parse_utils_checks_one.c parse/parse_utils_one.c parse/parse_utils_two.c \
		parse/parse_expand_utils.c parse/parse_extract_utils.c parse/parse_utils_checks_two.c parse/parse_utils_quotes_one.c \
		parse/parse_expand_utils_three.c parse/parse_line.c parse/parse_utils_malloc.c parse/parse_utils_quotes_two.c \
		\
		execute/builtine.c execute/ex_in_childs.c execute/export.c execute/ft_env.c execute/ft_exit.c \
		execute/cd.c execute/execute.c execute/export_utils.c execute/ft_error.c execute/ft_pwd.c execute/redirection.c \
		execute/echo.c execute/execve_utils.c execute/ft_convert_env.c execute/ft_execve.c execute/ft_unset.c execute/type_redirection.c

OBJS	= $(SRCS:.c=.o)

CFLAGS	=  -fsanitize=address -Wall -Wextra -Werror
RFLAGS	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include


all		: $(NAME)

$(NAME)	: $(SRCS)
	@make -C ./libft/
#	@make clean -C ./libft/

	gcc $(CFLAGS) $(RFLAGS) $(SRCS) ./libft/libft.a -o $(NAME) && echo "\033[1;37mCollecting sea shells...\033[0;38m"

clean	:
	@/bin/rm -rf *.o a.out 2&> /dev/null
	make clean -C ./libft

fclean	: clean
	@/bin/rm -rf $(NAME) $(NAME).dSYM 2&> /dev/null
	make fclean -C ./libft

re		: fclean all

.PHONY	: re fclean clean all
