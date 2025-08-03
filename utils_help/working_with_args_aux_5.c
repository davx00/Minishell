/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_with_args_aux_5.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 22:00:28 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 02:36:11 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

char	**allocate_and_fill_result(char const *s,
	char *separators, int word_count, int indices[3])
{
	char	**result;

	result = malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result = ft_fill_array(result, s, separators, indices);
	result[word_count] = NULL;
	return (result);
}

char	**clean_and_split(char const *s, char *separators)
{
	int		word_count;
	int		position;
	int		temp_word_count;
	int		indices[3];

	if (!s)
		return (NULL);
	initialize_split_variables(&word_count,
		&position, &temp_word_count, indices);
	word_count = validate_and_count_words(s, separators,
			&position, &temp_word_count);
	if (word_count == -1)
		return (NULL);
	return (allocate_and_fill_result(s, separators, word_count, indices));
}

int	process_command_creation(char **args, t_console *terminal)
{
	t_command		*cmd;
	t_command_nodes	*node;
	int				redirect_result;

	cmd = create_command(args);
	if (!cmd)
		return (0);
	redirect_result = process_all_redirections(args, cmd);
	if (redirect_result == -1)
		return (-1);
	node = create_command_node(cmd);
	if (node)
		add_node_to_list(&terminal->command_nodes, node);
	return (0);
}

int	handle_redirection_error(char **args, int *j)
{
	perror("redirection failure");
	if (args)
		ft_free_matrix(&args);
	(*j)++;
	return (-1);
}
