/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_not_builtin_2_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:47:00 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 21:13:43 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

char	*build_command_path(char *path_dir, char *command)
{
	char	*whole_path_filtered;
	char	*command_to_execute;

	whole_path_filtered = ft_strjoin(path_dir, "/");
	command_to_execute = ft_strjoin(whole_path_filtered, command);
	free(whole_path_filtered);
	return (command_to_execute);
}
