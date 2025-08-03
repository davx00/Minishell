/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_help_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:13:24 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 10:33:20 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

static void	handle_cd_two_args(char **args, char **target_dir,
	t_console *terminal, DIR **dir)
{
	if (ft_strcmp(args[1], "-") == 0)
	{
		handle_cd_dash(terminal);
		return ;
	}
	*target_dir = args[1];
	file_permission_error(*target_dir, dir);
	g_exit_code = 0;
}

static int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

void	check_and_exec_cd(char **str[2], t_console *terminal)
{
	char	**args;
	int		arg_count;
	char	*target_dir;
	DIR		*dir;

	init_check_and_exec_cd(&args, str, &arg_count, &target_dir);
	arg_count = count_args(args);
	if (arg_count == 1)
	{
		check_and_exec_cd_case_one(&target_dir, terminal);
		free(target_dir);
		target_dir = NULL;
		return ;
	}
	else if (arg_count == 2)
		handle_cd_two_args(args, &target_dir, terminal, &dir);
	else
		else_perror();
}

static char	*get_home_directory(t_console *terminal)
{
	char	*home_value;

	home_value = mini_getenv("HOME", terminal, 4);
	if (!home_value)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		g_exit_code = 1;
		return (NULL);
	}
	return (home_value);
}

void	check_and_exec_cd_case_one(char **target_dir, t_console *terminal)
{
	if (*target_dir)
	{
		free(*target_dir);
		*target_dir = NULL;
	}
	*target_dir = get_home_directory(terminal);
	if (!*target_dir)
		return ;
	if (chdir(*target_dir) != 0)
	{
		perror("cd");
		g_exit_code = 1;
		free(*target_dir);
		*target_dir = NULL;
		return ;
	}
	free(*target_dir);
	*target_dir = NULL;
	g_exit_code = 0;
}
