NAME = minishell

SRCS =	main.c									\

OBJS	= $(SRCS:.c=.o)

#LIBFT_A = libft.a

# COMPILER FLAGS
CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -I.

#-Ilibft en CFLAGS

all: $(NAME)
#bonus: all

$(NAME): $(OBJS) $(LIBFT_A)
			$(CC) $(CCFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)
#Añadir $(LIBFT_A) detras de OBJS
#Aadir $(LIBFT_A) entre OBJS y -o NAME

#$(LIBFT_A):
#		make -C libft
#		cp libft/libft.a .
clean:
#		make -C libft clean
		rm -f $(OBJS)
fclean: clean
#		make -C libft fclean
#		rm -f libft.a
		rm -f $(NAME)
re: fclean all