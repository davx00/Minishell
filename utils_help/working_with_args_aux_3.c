/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_with_args_aux_3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 21:55:06 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 02:36:11 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

int	handle_heredoc(char **args, t_command *cmd, int *i)
{
	if (cmd->heredoc_delimiter)
	{
		free(cmd->heredoc_delimiter);
		cmd->heredoc_delimiter = NULL;
	}
	cmd->heredoc_delimiter = ft_strdup(args[*i + 1]);
	cmd->redirect_heredoc = 1;
	cmd->redirect_input = 0;
	*i += 2;
	return (0);
}

int	handle_input_redirect(char **args, t_command *cmd, int *i)
{
	if (cmd->input_file)
	{
		free(cmd->input_file);
		cmd->input_file = NULL;
	}
	cmd->input_file = ft_strdup(args[*i + 1]);
	cmd->redirect_input = 1;
	*i += 2;
	return (0);
}

int	handle_append_redirect(char **args, t_command *cmd, int *i)
{
	add_output_file(cmd, args[*i + 1], 1);
	if (cmd->output_file)
	{
		free(cmd->output_file);
		cmd->output_file = NULL;
	}
	cmd->output_file = ft_strdup(args[*i + 1]);
	cmd->redirect_append = 1;
	cmd->redirect_output = 0;
	*i += 2;
	return (0);
}

int	handle_output_redirect(char **args, t_command *cmd,
		int *i, t_clean_args *clean)
{
	if (is_builtin_command(args[*i + 1]))
	{
		clean->args[*clean->index] = ft_strdup(args[*i]);
		(*clean->index)++;
		(*i)++;
	}
	else
	{
		add_output_file(cmd, args[*i + 1], 0);
		if (!cmd->redirect_append)
		{
			if (cmd->output_file)
			{
				free(cmd->output_file);
				cmd->output_file = NULL;
			}
			cmd->output_file = ft_strdup(args[*i + 1]);
			cmd->redirect_output = 1;
		}
		*i += 2;
	}
	return (0);
}

int	handle_empty_command(t_command *cmd, char **clean_args, int *clean_index)
{
	if (cmd->redirect_heredoc)
	{
		clean_args[0] = ft_strdup("cat");
		clean_args[1] = NULL;
		*clean_index = 1;
	}
	else if (cmd->redirect_output || cmd->redirect_append)
	{
		clean_args[0] = ft_strdup("true");
		clean_args[1] = NULL;
		*clean_index = 1;
	}
	else
	{
		ft_free_matrix(&clean_args);
		fprintf(stderr, "minishell: syntax error near unexpected token `<<'\n");
		return (-1);
	}
	return (0);
}
