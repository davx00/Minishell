/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:40:19 by akamal-b          #+#    #+#             */
/*   Updated: 2024/10/03 12:41:02 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_substr;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	new_substr = (char *)malloc((len + 1) * sizeof(char));
	if (!new_substr)
		return (NULL);
	ft_strlcpy(new_substr, s + start, len + 1);
	return (new_substr);
}
/*
#include <stdio.h>
int main(void)
{
	printf("%s", ft_substr("Hola world", 3, 10));
	return (0);
}
*/
