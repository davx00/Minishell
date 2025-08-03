NAME		= libft.a 

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LIB			= ar -rcs
LIB1		= ranlib
RM			= /bin/rm -f

INCS		= libft.h
SRCS		= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_printf.c ft_matrix_clone.c ft_matrix_add_row.c \
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
			ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_strcmp.c \
			ft_extend_array.c ft_array_len.c ft_free_matrix.c ft_strchr_index.c \
			ft_char_in_chars.c  ft_matrix_replace_index.c ft_clear_matrix.c\
			ft_count_words_and_quotes.c ft_count_words_utils.c
SRCS_BONUS	= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
			ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstadd_back_bonus.c ft_lstiter_bonus.c \
			ft_lstmap_bonus.c

OBJS		= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJS) $(INCS)
			$(LIB)	$(NAME) $(OBJS)
			$(LIB1) $(NAME)

bonus:		$(NAME) $(OBJS_BONUS)
			$(LIB)	$(NAME) $(OBJS_BONUS)
			$(LIB1) $(NAME)

.c.o: 		
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:		
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

rebonus:	fclean bonus

# Debe cumplir estos comandos
# $(NAME)
# all
# clean
# fclean
# re
