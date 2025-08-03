/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_help_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 22:42:58 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 21:13:43 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	file_permission_error(char *target_dir, DIR **dir)
{
	if (file_permission_error_2(target_dir))
		return ;
	*dir = opendir(target_dir);
	if (!*dir)
	{
		cd_error_no_directory(target_dir);
		return ;
	}
	closedir(*dir);
	if (chdir(target_dir) != 0)
	{
		cd_error_no_such_file(target_dir);
		return ;
	}
}

int	file_permission_error_2(char *target_dir)
{
	struct stat	st;

	if (access(target_dir, F_OK) != 0)
	{
		cd_error_no_such_file(target_dir);
		return (1);
	}
	if (stat(target_dir, &st) != 0 || !S_ISDIR(st.st_mode))
	{
		cd_error_no_directory(target_dir);
		return (1);
	}
	if (access(target_dir, R_OK | X_OK) != 0)
	{
		cd_error_permission_denied(target_dir);
		return (1);
	}
	return (0);
}

void	handle_cd_dash_util(char *oldpwd, char	*current_pwd)
{
	perror("cd");
	g_exit_code = 1;
	free(oldpwd);
	if (current_pwd)
		free(current_pwd);
}
