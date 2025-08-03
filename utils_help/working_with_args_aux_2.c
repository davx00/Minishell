/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_with_args_aux_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:05:38 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 11:01:17 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

static int	count_args(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

int	validate_clean_command(t_command *cmd, char **clean_args, int *clean_index)
{
	if (*clean_index == 0)
	{
		if (handle_empty_command(cmd, clean_args, clean_index) == -1)
			return (-1);
	}
	if (*clean_index == 0 && !cmd->redirect_output && !cmd->redirect_append)
	{
		ft_free_matrix(&clean_args);
		fprintf(stderr, "minishell: syntax error near unexpected token `<<'\n");
		return (-1);
	}
	return (0);
}

int	process_all_redirections(char **args, t_command *cmd)
{
	char	**clean_args;
	int		arg_count;
	int		clean_index;

	arg_count = count_args(args);
	clean_index = 0;
	if (!args || !cmd)
		return (0);
	clean_args = malloc((arg_count + 1) * sizeof(char *));
	if (!clean_args)
		return (-1);
	process_argument_loop(args, cmd, clean_args, &clean_index);
	clean_args[clean_index] = NULL;
	if (validate_clean_command(cmd, clean_args, &clean_index) == -1)
		return (-1);
	return (finalize_command(cmd, clean_args));
}

int	process_single_command(char *command_str, t_console *terminal)
{
	char	**args;
	int		result;

	args = clean_and_split(command_str, " \t");
	if (!args)
		return (-1);
	result = 0;
	if (args && args[0])
		result = process_command_creation(args, terminal);
	if (args)
	{
		ft_free_matrix(&args);
		args = NULL;
	}
	return (result);
}

void	process_command_matrix(char **command_matrix, t_console *terminal)
{
	int	j;
	int	result;

	j = 0;
	if (!command_matrix)
		return ;
	while (command_matrix[j])
	{
		result = process_single_command(command_matrix[j], terminal);
		if (result == -1)
		{
			j++;
			continue ;
		}
		j++;
	}
}
