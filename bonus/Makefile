SRCS		=	./srcs/pipex.c ./srcs/init.c ./srcs/check.c ./srcs/errors_handling.c ./srcs/path.c ./srcs/pipe.c ./srcs/utils.c

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
			make -C ./libft/get_next_line
			cp ./libft/get_next_line/libgnl.a ./lib
			$(CC) $(CFLAGS) ${OBJS} -g3 -L./lib -lft -lprintf -lgnl -o $(PIPEX)

clean:
			rm -rf ./srcs/*.o
			rm -rf ./srcs/*.d
			
fclean:		clean
			rm -rf $(PIPEX) ./lib/*.a

re:			fclean all

-include : $(DEPS)

.PHONY:		all clean fclean re