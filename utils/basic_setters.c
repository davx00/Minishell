/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:04:33 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 16:53:38 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

void	set_cwd(t_console *terminal, char **aux)
{
	*aux = getcwd(NULL, 0);
	if (!*aux)
		*aux = ft_strdup("/");
	mini_setenv("PWD", 3, terminal, aux);
	free(*aux);
	*aux = NULL;
}

void	set_shlvl(t_console *terminal, char **aux)
{
	char	*num_aux;

	num_aux = NULL;
	if (*aux)
	{
		free(*aux);
		*aux = NULL;
	}
	*aux = mini_getenv("SHLVL", terminal, 5);
	if (!*aux || ft_atoi(*aux) <= 0)
		*aux = ft_strdup("1");
	else
	{
		num_aux = ft_strdup(*aux);
		free(*aux);
		*aux = NULL;
		*aux = ft_itoa(ft_atoi(num_aux) + 1);
		free(num_aux);
		num_aux = NULL;
	}
	mini_setenv("SHLVL", 5, terminal, aux);
	if (num_aux && *num_aux)
		free(num_aux);
}

void	set_path(t_console *terminal, char **aux)
{
	if (*aux)
	{
		free(*aux);
		*aux = NULL;
	}
	*aux = mini_getenv("PATH", terminal, 4);
	if (!*aux)
	{
		*aux = ft_strdup("/usr/local/sbin:/usr/local/bin:/usr/bin:/bin");
		mini_setenv("PATH", 4, terminal, aux);
		return ;
	}
	if (*aux && **aux)
	{
		free(*aux);
		*aux = NULL;
	}
}

void	set_underscore(t_console *terminal, char **aux, char *str)
{
	char	*str_duped;

	if (*aux && **aux)
	{
		free(*aux);
		*aux = NULL;
	}
	*aux = mini_getenv("_", terminal, 1);
	str_duped = ft_strdup(str);
	if (!*aux)
		mini_setenv("_", 1, terminal, &str_duped);
	if (str_duped)
	{
		free(str_duped);
		str_duped = NULL;
	}
	if (*aux)
	{
		free(*aux);
		*aux = NULL;
	}
}
