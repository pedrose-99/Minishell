NAME = minishell

SRCS =	srcs/built-ins.c \
	srcs/lst_functions.c \
	srcs/env_lst_functions.c \
	srcs/utils.c \
	srcs/built-ins/cd.c srcs/built-ins/echo.c srcs/built-ins/export.c srcs/built-ins/pwd.c srcs/built-ins/unset.c

	
OBJS	= $(SRCS:.c=.o)

LIBFT_A = libft.a

CC		= gcc

CCFLAGS	= -Wall -Werror -Wextra -lreadline -Ilibft  -I.

#-Ilibft en CFLAGS

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
			$(CC) $(CCFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)

$(LIBFT_A):
		#make -C libft
		#cp libft/libft.a .
clean:
		#make -C libft clean
		rm -f $(OBJS)
fclean: clean
		@make -C libft fclean
		#rm -f libft.a
		rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re  