# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/03 02:16:18 by despanol          #+#    #+#              #
#    Updated: 2025/08/03 08:41:41 by despanol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Werror -Wextra -g3 -Iheads
RM          = rm -f
AR          = ar rcs

# Librería Libft
LIBFT_DIR   = libft
LIBFT_A     = $(LIBFT_DIR)/libft.a

# Archivos de cabecera
INC         = heads/mini.h

# Directorios de código fuente
UTILS       = utils/
UTILS_HELP  = utils_help/
GNL         = gnl/
SRC         = src/

# Fuentes
SRCS        = $(SRC)main_utils_signal.c \
              $(SRC)main_main.c \
              $(SRC)main_main_main.c \
              $(GNL)get_next_line.c \
              $(GNL)get_next_line_aux.c \
              $(UTILS)error_terminal.c \
              $(UTILS)utils_terminal.c \
              $(UTILS)utils_matrix.c \
              $(UTILS)utils_envp.c \
              $(UTILS)basic_setters.c \
              $(UTILS)command_line_decor.c \
              $(UTILS)execute_command.c \
              $(UTILS)free_all.c \
              $(UTILS)working_with_args.c \
              $(UTILS_HELP)working_with_args_aux_2.c \
              $(UTILS_HELP)working_with_args_aux.c \
              $(UTILS_HELP)working_with_args_helper_utils_1.c \
              $(UTILS_HELP)working_with_args_helper.c \
              $(UTILS_HELP)pipe_split_utils.c \
              $(UTILS)ft_fill_array.c \
              $(UTILS_HELP)pre_execution_utils_1.c \
              $(UTILS_HELP)pre_execution_utils_2.c \
              $(UTILS_HELP)pre_execution_utils_3.c \
              $(UTILS)pre_execution.c \
              $(UTILS_HELP)pipex_integration_utils_1.c \
              $(UTILS_HELP)pipex_integration_utils_2.c \
              $(UTILS_HELP)pipex_integration_utils_3.c \
              $(UTILS_HELP)pipex_integration_utils_4.c \
              $(UTILS)pipex_integration.c \
              $(UTILS)builtin_cd.c \
              $(UTILS)builtin_exit.c \
              $(UTILS)builtin_export.c \
              $(UTILS)builtin_unset.c \
              $(UTILS)builtin_pwd.c \
              $(UTILS)builtin_echo.c \
              $(UTILS)builtin_env.c \
              $(UTILS)builtin_true.c \
              $(UTILS)builtin_utils.c \
              $(UTILS)exec_not_builtin.c \
              $(UTILS)simple_free.c \
              $(UTILS_HELP)exec_not_builtin_utils.c \
              $(UTILS_HELP)exec_not_builtin_utils_1.c \
              $(UTILS_HELP)exec_not_builtin_utils_2.c \
              $(UTILS_HELP)exec_not_builtin_help.c \
              $(UTILS)translate_vars_to_data.c \
              $(UTILS_HELP)translate_vars_to_data_utils.c \
              $(UTILS)heredoc.c \
              $(UTILS_HELP)heredoc_utils_1.c \
              $(UTILS_HELP)heredoc_utils_help_2.c \
              $(UTILS_HELP)builtin_utils_1.c \
              $(UTILS_HELP)redirection_utils.c \
              $(UTILS)check_redir_and_pipes_syntax.c \
              $(UTILS_HELP)builtin_cd_help.c \
              $(UTILS_HELP)builtin_cd_help_1.c \
              $(UTILS_HELP)builtin_cd_help_2.c \
              $(UTILS_HELP)check_redir_and_pipes_utils.c \
              $(UTILS_HELP)check_and_redir_pipes_utils_2.c \
              $(UTILS_HELP)free_all_utils.c \
              $(UTILS_HELP)exec_not_builtin_2_2.c \
              $(UTILS_HELP)working_with_args_aux_3.c \
              $(UTILS_HELP)working_with_args_aux_4.c \
              $(UTILS_HELP)working_with_args_aux_5.c \
              $(UTILS_HELP)working_with_args_aux_6.c \
              $(UTILS_HELP)translate_vars_helper.c \
              main.c

OBJS        = $(SRCS:.c=.o)

# Regla principal
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -lreadline -o $(NAME)

# Compilación de objetos
%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilar libft sólo si es necesario
$(LIBFT_A):
	$(MAKE) bonus -C $(LIBFT_DIR)

# Limpiar objetos
clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

# Limpiar todo
fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

# Recompilar todo
re: fclean all

.PHONY: all clean fclean re
