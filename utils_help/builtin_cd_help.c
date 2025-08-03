/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:35:25 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 16:57:58 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	else_perror(void)
{
	perror("minishell: cd: too many arguments\n");
	g_exit_code = 1;
	return ;
}

void	cd_error_no_such_file(char *target_dir)
{
	write(2, "minishell: cd: ", 15);
	write(2, target_dir, strlen(target_dir));
	write(2, ": No such file or directory\n", 28);
	g_exit_code = 1;
	return ;
}

void	cd_error_no_directory(char *target_dir)
{
	write(2, "minishell: cd: ", 15);
	write(2, target_dir, strlen(target_dir));
	write(2, ": Not a directory\n", 18);
	g_exit_code = 1;
	return ;
}

void	cd_error_permission_denied(char *target_dir)
{
	write(2, "minishell: cd: ", 15);
	write(2, target_dir, strlen(target_dir));
	write(2, ": Permission denied\n", 20);
	g_exit_code = 1;
	return ;
}
