/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:48:51 by codespace         #+#    #+#             */
/*   Updated: 2025/08/03 03:07:37 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H

# define MINI_H
# define BUFFER_SIZE 42
# define READ_END 0
# define WRITE_END 1

# include <asm/termbits.h>

# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <sys/types.h>
# include <stddef.h>
# include <sys/ioctl.h>
# include <sys/stat.h>

# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# include "../libft/libft.h"

// Structs
typedef struct s_pipeline_vars
{
	int		prev_fd;
	int		cmd_count;
	int		i;
	int		temp_status;
	int		is_last;
	int		output_fd;
	int		is_last_command;
	int		*heredoc_fds;
	char	*command;
	int		pipe_fd[2];
	pid_t	*pids;
}	t_pipeline_vars;

typedef struct s_command
{
	char	**splitted_command;
	char	*source_command;
	int		infile;
	int		outfile;
	char	*output_file;
	char	*input_file;
	t_list	*output_files;
	t_list	*append_files;
	char	*heredoc_delimiter;
	int		redirect_output;
	int		redirect_append;
	int		redirect_input;
	int		redirect_heredoc;
}	t_command;

typedef struct s_command_nodes
{
	t_command				*command;
	struct s_command_nodes	*next;
}	t_command_nodes;

typedef struct s_console
{
	t_command_nodes	*command_nodes;
	char			**envp;
	char			**argv;
	char			*command_line_decor;
	char			*out;
	char			**command_result;
	pid_t			pid;
}	t_console;

typedef struct s_signal_data
{
	int	is_waiting_for_input;
	int	is_blocking_command;
}	t_signal_data;

typedef struct s_clean_args
{
	char	**args;
	int		*index;
}	t_clean_args;

// Util's utils
int				is_inside_quotes(char *str, int i, int *quotes);
int				should_expand_variable(char *str, int i, int *quotes);
char			*get_substr_var(char *str, int i, t_console *prompt);
char			*expand_string(char *str, int i,
					int *quotes, t_console *prompt);
char			*build_expanded_string(char *str, int i, int pos, char *var);

// Helper functions from working_with_args_helper.c
void			init_quote_vars(int *vars, char *quote_char);
char			*remove_quotes(char *str);
void			skip_separators(const char *s, char *separators, int *index);
void			process_word(const char *s, char *separators,
					int *quotes, int *index);
char			*create_clean_word(const char *s, int start_pos, int end_pos);
void			process_quote_removal(char *str, char *result,
					int *vars, char *quote_char);

// Pipe splitting utilities
char			**split_by_pipes_preserve_quotes(char const *s);

// Utils
void			process_command_matrix(char **command_matrix,
					t_console *terminal);
int				process_all_redirections(char **args, t_command *cmd);
void			set_cwd(t_console *terminal, char **aux);
void			set_shlvl(t_console *terminal, char **aux);
void			set_path(t_console *terminal, char **aux);
void			set_underscore(t_console *terminal, char **aux, char *str);
void			set_father_pid(t_console *terminal);
void			mini_setenv(char *var_name, int n,
					t_console *terminal, char **value);
char			*mini_getenv(char *var_name, t_console *terminal, int n);
void			set_command_line_decor(t_console *terminal);
void			execute_command(t_console *terminal, char *executable_path,
					char *executable_args);
int				work_with_args(t_console *terminal);
t_command		*create_command(char **args);
t_command_nodes	*create_command_node(t_command *command);
void			add_node_to_list(t_command_nodes **head,
					t_command_nodes *new_node);
char			**ft_fill_array(char **result,
					const char *s, char *separators, int indices[3]);
int				word_counter_custom(const char *s, const char *set, int count);
void			basic_builtin_exec(t_console *terminal);
void			execute_single_command(t_console *terminal,
					t_command_nodes *current_node);
int				validate_syntax(char *command_line);
void			handle_cd_dash_util(char *oldpwd, char	*current_pwd);
int				handle_cd_dash(t_console *terminal);
void			init_check_and_exec_cd(char ***args, char **str[2],
					int *arg_count, char **target_dir);
void			check_and_exec_cd(char **str[2], t_console *terminal);

// Pre-execution helper functions
int				validate_single_command(t_console *terminal,
					t_command_nodes *current_node);
int				handle_output_files(t_command_nodes *current_node,
					t_console *terminal, int *stdin_backup, int *stdout_backup);
int				handle_redirections(t_command_nodes *current_node,
					int *stdin_backup, int *stdout_backup);
void			setup_input_redirection(t_command_nodes *current_node,
					int *stdin_backup);
void			setup_output_redirection(t_command_nodes *current_node,
					int *stdout_backup);
void			execute_command_dispatch(char *command,
					t_console *terminal, t_command_nodes *current_node);
void			restore_redirections(int stdin_backup, int stdout_backup);

// Pipe management functions

void			restore_pipe_redirections(int backup_fds);
int				setup_pipe_redirections(int input_fd, int output_fd);
void			exec_execute_command(char *command, t_console *terminal);
int				count_commands_in_pipeline(t_command_nodes *commands);
int				is_builtin_command(char *command);

int				setup_heredoc(t_command *cmd);
int				setup_heredoc_single(t_command *cmd);
int				allocate_pipeline_resources(int cmd_count,
					pid_t **pids, int **heredoc_fds);
void			pipeline_cleanup(pid_t *pids, int *heredoc_fds);
void			setup_pipeline_vars(t_pipeline_vars *vars,
					t_command_nodes *command_nodes, pid_t *pids);
void			execute_pipeline_loop(t_console *terminal,
					t_pipeline_vars *vars);
int				execute_pipeline_pipex_style(t_console *terminal);
int				is_builtin_command(char *command);
void			execute_builtin_in_pipe(t_console *terminal,
					t_command_nodes *cmd_node, int input_fd, int output_fd);
int				count_commands_in_pipeline(t_command_nodes *commands);
int				check_heredoc_line(char *line,
					char *delimiter, size_t delimiter_len);
int				loop_heredoc_lines(int pipe_fd[2],
					char *delimiter, size_t delimiter_len, char *prompt);

// Environment functions (equivalent to your mini_* functions)
char			*mini_getenv_terminal(char *var, char **envp, int n);
char			**mini_setenv_terminal(char *var,
					char *value, char **envp, int n);

// CD helper functions
void			cd_error(char **str[2]);

// GNL
char			*get_next_line(int fd);
void			ft_cleanup_gnl(char **keep, char **line);
char			*ft_update_static(const char *keep);

// Error
void			mini_perror(int err_type, char *param, int err);
void			print_error(int err_type, char *param, int err);
void			print_error_exit(int err_type, char *param, int err);

char			**matrix_dup(char **matrix);

// Free all
void			free_all_console_2(t_console *terminal);
void			free_all_console(t_console *terminal);
void			free_all_console_child(t_console *terminal);
void			free_command_nodes(t_command_nodes *cmds);
void			simple_free(char *data);
void			free_command(t_command *command);
void			free_console_strings_2(t_console *terminal);
void			free_console_strings(t_console *terminal);
void			free_console_matrices(t_console *terminal);

//main_utils_signal.c
void			start_terminal(char **argv, char **envp, t_console *terminal);
void			init_terminal_env_vars(t_console *terminal, char **argv);
void			simulate_enter(void);
void			function_handler(int signal);

// main_main.c
void			init_signals(t_console *terminal, t_signal_data *signal_data);
void			error_usage(t_console *terminal, char **argv);
void			ft_count_words_aux(void);
void			free_clean(t_console *terminal);
void			start_terminal_set_pid(char **argv,
					char **envp, t_console *terminal);
void			while_aux(t_console *terminal);
void			while_continue(t_console *terminal, t_signal_data signal_data);

// main.c
t_signal_data	*get_signal_data(void);

//builtin_help
// void	check_and_exec_cd_case_one(char **target_dir, char **str[2]);
void			check_and_exec_cd_case_one(char **target_dir,
					t_console *terminal);
void			else_perror(void);
void			cd_error_no_such_file(char *target_dir);
void			cd_error_no_directory(char *target_dir);
void			cd_error_permission_denied(char *target_dir);
void			file_permission_error(char *target_dir, DIR **dir);
int				file_permission_error_2(char *target_dir);
void			exec_child(t_command_nodes *cmd_node,
					t_console *terminal, t_pipeline_vars vars);
void			init_heredoc_fds(t_command_nodes *head,
					t_pipeline_vars *vars, pid_t *pids);
void			wait_and_set_exit_status(pid_t *pids, t_pipeline_vars *vars);
void			fork_and_exec_child(t_command_nodes *current,
					t_console *terminal, t_pipeline_vars *vars);
void			close_fds_after_child(t_pipeline_vars *vars, int *pipe_fd);
void			add_output_file(t_command *cmd, char *filename, int is_append);
void			create_all_output_files(t_command *cmd, t_console *terminal);
void			print_envp(char **envp);
void			export_var_no_value(char *arg, t_console *terminal);
void			export_var_with_value(char *arg, int pos, t_console *terminal);
char			*get_path_no_env(char *command);
char			*get_path_env(char *command, char **whole_path_no_colon);
int				is_directory(const char *path);
char			*check_direct_access(char *command);
char			*search_in_path(char *command,
					char **whole_path_no_colon, int row);
void			update_quote_state(char current,
					int *in_quotes, char *quote_char);
int				check_double_pipe(char *str, int i);
int				check_redir_followed_by_operator(char *str,
					int i, int redir_len);
int				check_pipe_followed_by_invalid(char *str, int i);
int				check_consecutive_operators(char *str);
int				is_redirection_operator(char *str, int i);
int				process_char_outside_quotes(char *str, int *i);
int				handle_execve_and_wait(char *executable_path,
					t_command_nodes *node, t_console *terminal);
char			*handle_readline_input(int *sigint_received);

// Built-in command functions
int				find_var_in_envp(char *var_name, char **envp);
void			check_and_exec_cd(char **str[2], t_console *terminal);
int				exec_built_cd(t_console *terminal);
int				exec_built_exit(t_console *terminal);
int				exec_built_export(t_console *terminal);
int				exec_built_unset(t_console *terminal);
int				exec_built_pwd(void);
int				exec_built_echo(t_console *terminal);
int				exec_built_env(t_console *terminal);
void			exec_built_true(void);
int				exec_not_builtin(t_console *terminal,
					t_command_nodes *node, t_pipeline_vars *vars);
int				exec_not_builtin_standalone(t_command_nodes *node,
					t_console *terminal);
void			wait_and_set_exit(int status);
void			dir_error(const char *command);
void			perm_error(const char *command);
void			cmd_not_found(const char *command);
void			execve_error(char *command,
					char *executable_path, t_console *terminal);
void			execve_child(char *executable_path,
					t_command_nodes *node, t_console *terminal);
char			*build_command_path(char *path_dir, char *command);
int				should_exit_heredoc(char *line,
					char *delimiter, size_t delimiter_len);
void			write_line_to_pipe(int pipe_fd[2], char *line);
int				validate_clean_command(t_command *cmd,
					char **clean_args, int *clean_index);
int				process_single_command(char *command_str, t_console *terminal);
int				handle_heredoc(char **args, t_command *cmd, int *i);
int				handle_input_redirect(char **args, t_command *cmd, int *i);
int				handle_append_redirect(char **args, t_command *cmd,
					int *i);
int				handle_output_redirect(char **args, t_command *cmd,
					int *i, t_clean_args *clean);
int				handle_empty_command(t_command *cmd, char **clean_args,
					int *clean_index);
int				process_argument_loop(char **args,
					t_command *cmd,
					char **clean_args,
					int *clean_index);
int				finalize_command(t_command *cmd,
					char **clean_args);
int				finalize_command(t_command *cmd,
					char **clean_args);
void			initialize_split_variables(int *word_count,
					int *position,
					int *temp_word_count,
					int indices[3]);
int				validate_and_count_words(char const *s, char *separators,
					int *position, int *temp_word_count);
char			**allocate_and_fill_result(char const *s, char *separators,
					int word_count, int indices[3]);
char			**clean_and_split(char const *s, char *separators);
int				process_command_creation(char **args, t_console *terminal);
int				handle_redirection_error(char **args, int *j);
void			add_to_clean_args(char **args, int *i, char **clean_args,
					int *clean_index);
int				is_blocking_command(char *command);
void			handle_output_redirection(t_command_nodes *cmd_node,
					t_console *terminal, t_pipeline_vars *vars);

// Input/Output redirection functions
int				get_output_flags(t_command *cmd);
int				open_output_file(t_command *cmd, t_console *terminal,
					t_pipeline_vars *vars);
void			handle_heredoc_input(t_pipeline_vars *vars);
void			handle_file_input(t_command_nodes *cmd_node,
					t_console *terminal,
					t_pipeline_vars *vars);
void			handle_input_redirection(t_command_nodes *cmd_node,
					t_console *terminal, t_pipeline_vars *vars);

void			execute_command_child(t_command_nodes *cmd_node,
					t_console *terminal,
					t_pipeline_vars *vars);
void			mini_error(char *msg,
					t_console *terminal);
int				handle_fork_process(char *executable_path,
					t_command_nodes *node,
					t_console *terminal);
int				handle_path_error(char *command,
					t_signal_data *signal_data);
void			handle_signal_data(t_signal_data *signal_data, char *command);

#endif
