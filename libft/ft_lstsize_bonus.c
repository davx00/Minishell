/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:57:03 by akamal-b          #+#    #+#             */
/*   Updated: 2024/10/07 13:59:34 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		cont;
	t_list	*ptr;

	ptr = lst;
	cont = 0;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		cont++;
	}
	return (cont);
}
