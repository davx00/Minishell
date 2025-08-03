/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_not_builtin_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:35:31 by akamal-b          #+#    #+#             */
/*   Updated: 2025/08/03 04:33:22 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

char	*get_path_no_env(char *command)
{
	if (is_directory(command))
	{
		dir_error(command);
		return (NULL);
	}
	if (access(command, F_OK) == 0)
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		perm_error(command);
		return (NULL);
	}
	return (NULL);
}

char	*get_path_env(char *command, char **whole_path_no_colon)
{
	char	*result;

	if (is_directory(command))
	{
		dir_error(command);
		ft_free_matrix(&whole_path_no_colon);
		return (NULL);
	}
	if (ft_strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
		{
			ft_free_matrix(&whole_path_no_colon);
			return (ft_strdup(command));
		}
		perm_error(command);
		ft_free_matrix(&whole_path_no_colon);
		return (NULL);
	}
	result = search_in_path(command, whole_path_no_colon, -1);
	if (result)
		return (result);
	ft_free_matrix(&whole_path_no_colon);
	return (NULL);
}

int	is_directory(const char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

char	*check_direct_access(char *command)
{
	if (access(command, F_OK) == 0)
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		fprintf(stderr, "minishell: %s: Permission denied\n", command);
		g_exit_code = 126;
		return (NULL);
	}
	return (NULL);
}

char	*search_in_path(char *command, char **whole_path_no_colon, int row)
{
	char	*command_to_execute;
	DIR		*dir;

	while (whole_path_no_colon[++row])
	{
		command_to_execute = build_command_path(whole_path_no_colon[row],
				command);
		if (access(command_to_execute, F_OK) == 0)
		{
			dir = opendir(command_to_execute);
			if (dir)
			{
				closedir(dir);
				free(command_to_execute);
				command_to_execute = NULL;
				continue ;
			}
			if (access(command_to_execute, X_OK) == 0)
				return (ft_free_matrix(&whole_path_no_colon),
					command_to_execute);
		}
		free(command_to_execute);
		command_to_execute = NULL;
	}
	return (NULL);
}
