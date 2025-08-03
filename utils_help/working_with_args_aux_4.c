/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_with_args_aux_4.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 21:57:20 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 02:36:11 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

int	process_argument_loop(char **args, t_command *cmd,
		char **clean_args, int *clean_index)
{
	int				i;
	t_clean_args	clean;

	i = 0;
	clean.args = clean_args;
	clean.index = clean_index;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<<") == 0 && args[i + 1])
			handle_heredoc(args, cmd, &i);
		else if (ft_strcmp(args[i], "<") == 0 && args[i + 1])
			handle_input_redirect(args, cmd, &i);
		else if (ft_strcmp(args[i], ">>") == 0 && args[i + 1])
			handle_append_redirect(args, cmd, &i);
		else if (ft_strcmp(args[i], ">") == 0 && args[i + 1])
			handle_output_redirect(args, cmd, &i, &clean);
		else
		{
			clean_args[*clean_index] = ft_strdup(args[i]);
			(*clean_index)++;
			i++;
		}
	}
	return (0);
}

int	finalize_command(t_command *cmd, char **clean_args)
{
	if (cmd->splitted_command)
		ft_free_matrix(&cmd->splitted_command);
	cmd->splitted_command = clean_args;
	return (1);
}

void	initialize_split_variables(int *word_count, int *position,
		int *temp_word_count, int indices[3])
{
	indices[0] = 0;
	indices[1] = 0;
	indices[2] = 0;
	*word_count = 0;
	*position = 0;
	*temp_word_count = 0;
}

int	validate_and_count_words(char const *s, char *separators,
		int *position, int *temp_word_count)
{
	int	word_count;

	word_count = ft_count_words_and_quotes(s, separators,
			position, temp_word_count);
	if (word_count == -1)
	{
		write(2, "Error: Unmatched quote\n", 23);
		return (-1);
	}
	return (word_count);
}
