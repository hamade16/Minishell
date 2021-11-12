NAME	= minishell

SRCS	= main.c \
		shared_utils/minishell_utils_one.c shared_utils/minishell_utils_two.c \
		parse/*.c \
		execute/*.c


OBJS	= $(SRCS:.c=.o)

CFLAGS	= # -Wall -Wextra -Werror
RFLAGS	= -lreadline
DFLAGS	= -g -fsanitize=address

all		: $(NAME)

$(NAME)	:
	@make -C ./libft/
	@make clean -C ./libft/

	@gcc $(CFLAGS) $(RFLAGS) $(DFLAGS) $(SRCS) ./libft/libft.a -o $(NAME) && echo "\033[1;37mCollecting sea shells...\033[0;38m"

clean	:
	@/bin/rm -rf *.o a.out 2&> /dev/null
	make clean -C ./libft

fclean	: clean
	@/bin/rm -rf $(NAME) $(NAME).dSYM 2&> /dev/null
	make fclean -C ./libft

re		: fclean all
	./minishell

.PHONY	: re fclean clean all
