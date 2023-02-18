/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:12:26 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/08 14:12:26 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_s(const char *s)
{
	size_t	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*buff;
	size_t	i;

	i = -1;
	if (!s)
		return (NULL);
	buff = ft_calloc(sizeof(char), ft_strlen_s(s) + 1);
	if (!buff)
		return (NULL);
	while (s[++i])
		buff[i] = s[i];
	return (buff);
}
