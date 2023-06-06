SRCS =  ft_putchar_fd.c ft_strmapi.c ft_atoi.c ft_putendl_fd.c ft_strncmp.c ft_bzero.c \
		ft_strlcpy.c ft_calloc.c ft_memchr.c ft_strlen.c ft_isalnum.c ft_memcmp.c ft_strmapi.c ft_isalpha.c \
		ft_memcpy.c ft_strncmp.c ft_isascii.c ft_memmove.c ft_strnstr.c ft_isdigit.c ft_memset.c ft_strrchr.c \
		ft_isprint.c ft_putchar_fd.c ft_itoa.c ft_putendl_fd.c	ft_strtrim.c ft_putnbr_fd.c	\
		ft_substr.c  ft_putstr_fd.c ft_toupper.c ft_split.c ft_strchr.c  ft_strdup.c ft_tolower.c ft_striteri.c \
		aux_join.c ft_strlcat.c get_next_line.c aux_join.c longer_str.c \

SRCSB = ft_lstclear_bonus.c ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstiter_bonus.c \
		ft_lstlast_bonus.c ft_lstdelone_bonus.c ft_lstsize_bonus.c ft_lstnew_bonus.c ft_lstmap_bonus.c
		
OBJS = ${SRCS:.c=.o}

OBJSB = ${SRCSB:.c=.o}

CC = gcc -Wall -Werror -Wextra

NAME = libft.a

NAME_B = .bonusfile

.c.o:
	${CC} -c $< -o ${<:.c=.o} -I.

${NAME}:	${OBJS}
		ar rc ${NAME} ${OBJS}

all:		${NAME}

clean:
		rm -f ${OBJS} ${OBJSB}

fclean:		clean
		rm -f ${NAME}

re:		fclean all

bonus:		${NAME_B}

${NAME_B} : ${OBJS} ${OBJSB}
		ar rc ${NAME} ${OBJS} ${OBJSB}
		@touch ${NAME_B}

.PHONY: all clean fclean re bonus
