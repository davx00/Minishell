/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:53:28 by akamal-b          #+#    #+#             */
/*   Updated: 2025/08/02 21:19:20 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

static void	free_list_content(t_list *list)
{
	t_list	*current;
	t_list	*next;

	current = list;
	while (current)
	{
		next = current->next;
		simple_free(current->content);
		free(current);
		current = next;
	}
}

void	free_command(t_command *command)
{
	if (!command)
		return ;
	if (command->splitted_command)
		ft_free_matrix(&command->splitted_command);
	simple_free(command->source_command);
	simple_free(command->output_file);
	simple_free(command->heredoc_delimiter);
	simple_free(command->input_file);
	free_list_content(command->output_files);
	free_list_content(command->append_files);
	if (command->infile > 2)
		close(command->infile);
	if (command->outfile > 2)
		close(command->outfile);
	free(command);
	command = NULL;
}

void	free_console_strings_2(t_console *terminal)
{
	if (terminal->command_line_decor)
	{
		free(terminal->command_line_decor);
		terminal->command_line_decor = NULL;
	}
}

void	free_console_strings(t_console *terminal)
{
	if (terminal->out != NULL)
	{
		free(terminal->out);
		terminal->out = NULL;
	}
	if (terminal->command_line_decor)
	{
		free(terminal->command_line_decor);
		terminal->command_line_decor = NULL;
	}
}

void	free_console_matrices(t_console *terminal)
{
	if (terminal->envp && terminal->envp[0])
	{
		ft_free_matrix(&terminal->envp);
		terminal->envp = NULL;
	}
	if (terminal->argv && terminal->argv[0])
	{
		ft_free_matrix(&terminal->argv);
		terminal->argv = NULL;
	}
	if (terminal->command_result && terminal->command_result[0])
	{
		ft_free_matrix(&terminal->command_result);
		terminal->command_result = NULL;
	}
}
