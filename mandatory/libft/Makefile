NAME		=	libft.a

DIR_SRCS	=	libft

SRCS 		=	ft_atoi.c \
				ft_bzero.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_free_tab.c\
				ft_isdigit.c \
				ft_isprint.c \
				ft_calloc.c \
				ft_lstadd_back.c \
				ft_dup_tab.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strmapi.c \
				ft_itoa.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_split_utils.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlen.c \
				ft_str_tab_len.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_free_tab.c \
				ft_tablen.c \
				ft_strcmp.c \
				ft_check_empty.c \
				ft_malloc_less_itoa.c \
				ft_free_elem.c \
				ft_char_index.c \
				ft_numbered_str_only.c \

OBJS		=	$(SRCS:.c=.o)

DEPS		=	$(SRCS:.c.d)

OBJS_BONUS	=	$(BONUS:.c=.o)

INCLUDES	=	-I includes

CC			=	cc
CFLAGS		=	-g3 -Wall -Wextra -Werror

.c.o :	
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			ar -rcs $(NAME) $(OBJS)
			
all:		$(NAME)

bonus:		$(OBJS) $(OBJS_BONUS)
			ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

clean:
			rm -rf $(OBJS) $(OBJS_BONUS) $(DEPS)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

-include : 	$(DEPS)

.PHONY:		all clean fclean re