/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:04:37 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 17:36:10 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	init_check_and_exec_cd(char ***args, char **str[2],
	int *arg_count, char **target_dir)
{
	*args = str[0];
	*arg_count = 0;
	*target_dir = NULL;
}

static char	**init_cd_data(t_console *terminal)
{
	char	**data;
	char	*aux;

	aux = mini_getenv("HOME", terminal, 4);
	if (!aux)
		aux = ft_strdup("");
	data = ft_extend_array(NULL, aux);
	free(aux);
	aux = NULL;
	aux = getcwd(NULL, 0);
	data = ft_extend_array(data, aux);
	free(aux);
	aux = NULL;
	return (data);
}

static void	update_cd_env(t_console *terminal, char **data)
{
	char	*current_pwd;
	char	*old_pwd_copy;
	char	*current_pwd_copy;

	if (!g_exit_code && data[1])
	{
		old_pwd_copy = ft_strdup(data[1]);
		mini_setenv("OLDPWD", 6, terminal, &old_pwd_copy);
		free(old_pwd_copy);
	}
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
	{
		current_pwd = ft_strdup(data[0]);
	}
	current_pwd_copy = ft_strdup(current_pwd);
	mini_setenv("PWD", 3, terminal, &current_pwd_copy);
	free(current_pwd_copy);
	free(current_pwd);
}

int	handle_cd_dash(t_console *terminal)
{
	char	*oldpwd;
	char	*current_pwd;

	oldpwd = mini_getenv("OLDPWD", terminal, 6);
	if (!oldpwd)
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		g_exit_code = 1;
		return (1);
	}
	current_pwd = getcwd(NULL, 0);
	printf("%s\n", oldpwd);
	if (chdir(oldpwd) != 0)
	{
		handle_cd_dash_util(oldpwd, current_pwd);
		return (1);
	}
	mini_setenv("PWD", 3, terminal, &oldpwd);
	if (current_pwd)
		mini_setenv("OLDPWD", 6, terminal, &current_pwd);
	free(oldpwd);
	if (current_pwd)
		free(current_pwd);
	g_exit_code = 0;
	return (0);
}

int	exec_built_cd(t_console *terminal)
{
	char	**str[2];
	char	**cd_data;

	g_exit_code = 0;
	str[0] = terminal->command_nodes->command->splitted_command;
	cd_data = init_cd_data(terminal);
	str[1] = cd_data;
	check_and_exec_cd(str, terminal);
	update_cd_env(terminal, cd_data);
	if (cd_data)
	{
		ft_free_matrix(&cd_data);
	}
	return (g_exit_code);
}
