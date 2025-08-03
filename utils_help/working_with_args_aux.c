/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_with_args_aux.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:05:38 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 18:15:08 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

static void	init_command_fields(t_command *cmd)
{
	cmd->source_command = NULL;
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->redirect_output = 0;
	cmd->redirect_append = 0;
	cmd->output_file = NULL;
	cmd->input_file = NULL;
	cmd->output_files = NULL;
	cmd->append_files = NULL;
	cmd->redirect_input = 0;
	cmd->heredoc_delimiter = NULL;
	cmd->redirect_heredoc = 0;
}

t_command	*create_command(char **args)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->splitted_command = matrix_dup(args);
	if (!cmd->splitted_command)
	{
		free(cmd);
		return (NULL);
	}
	init_command_fields(cmd);
	return (cmd);
}

t_command_nodes	*create_command_node(t_command *command)
{
	t_command_nodes	*node;

	node = malloc(sizeof(t_command_nodes));
	if (!node)
		return (NULL);
	node->command = command;
	node->next = NULL;
	return (node);
}

void	add_node_to_list(t_command_nodes **head, t_command_nodes *new_node)
{
	t_command_nodes	*current;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

int	word_counter_custom(const char *s, const char *set, int count)
{
	int	q[2];
	int	i;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (s && s[i] != '\0')
	{
		count++;
		if (!ft_strchr(set, s[i]))
		{
			while ((!ft_strchr(set, s[i]) || q[0] || q[1]) && s[i] != '\0')
			{
				q[0] = (q[0] + (!q[1] && s[i] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i] == '\"')) % 2;
				i++;
			}
			if (q[0] || q[1])
				return (-1);
		}
		else
			i++;
	}
	return (count);
}
