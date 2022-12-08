SRCS		=	./srcs/pipex.c ./srcs/init.c ./srcs/check.c ./srcs/errors_handling.c ./srcs/path.c ./srcs/pipe.c

OBJS		= $(SRCS:.c=.o)

DEPS		= $(SRCS:.c=.d)

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -MMD

PIPEX		=	pipex

all:		$(PIPEX)

.c.o :	
			$(CC) -g3 $(CFLAGS) $(INCLUDES) -c $< -o $@

$(PIPEX):	${OBJS}
			make -C ./libft/ft_printf
			cp ./libft/ft_printf/libprintf.a ./lib
			make -C ./libft
			cp ./libft/libft.a ./lib
			$(CC) -g3 $(CFLAGS) ${OBJS} -L./lib -lft -lprintf -o $(PIPEX)

clean:
			rm -rf ./srcs/*.o
			rm -rf ./srcs/*.d
			
fclean:		clean
			rm -rf $(PIPEX) ./lib/libft.a ./lib/libprintf.a

re:			fclean all

-include : $(DEPS)

.PHONY:		all clean fclean re