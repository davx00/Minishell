/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:05:07 by despanol          #+#    #+#             */
/*   Updated: 2025/07/24 14:01:25 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	print_error(int err_type, char *param, int err)
{
	g_exit_code = err;
	if (err_type == 3)
		ft_putstr_fd("fork failed\n", 2);
	else if (err_type == 4)
		ft_putstr_fd("\" or \' not closed\n", 2);
	ft_putendl_fd(param, 2);
}

void	print_error_exit(int err_type, char *param, int err)
{
	g_exit_code = err;
	print_error(err_type, param, err);
	exit(1);
}
