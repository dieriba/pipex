/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:12:14 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/08 14:12:14 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_strlen_(const char *s)
{
	size_t	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
		;
	return (i);
}

int	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return (-1);
	else if (write (fd, s, ft_strlen_(s)) < 0)
		return (-1);
	return (0);
}
