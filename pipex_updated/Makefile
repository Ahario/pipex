SRCS = pipex.c ft_split.c pipex_utils.c pipex_error.c pipex_utils2.c
OBJS = ${SRCS:.c=.o}
CC    = gcc
CFLAGS	= -Wextra -Wall -Werror
NAME	= pipex
.c.o:		&{CC} &{CFLAGS} -c -o $@ $<

${NAME} : ${OBJS}
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all:  ${NAME}

clean:
	 rm -f ${OBJS}
	
fclean :	clean
	rm -f ${NAME}

re : fclean all clean

test: re
	./${NAME} a.c "ls -al" "wc -l" b.c

leaks: 
	leaks -atExit -- ./pipex

.Phony: all bonus clean fclean re
