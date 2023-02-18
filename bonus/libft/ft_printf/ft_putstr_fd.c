/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:15:17 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/11 18:15:17 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	size_t	ft_strlen_(const char *s)
{
	size_t	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

int	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (s != NULL)
	{
		len = ft_strlen_(s);
		write (fd, s, len);
	}
	else
	{
		write (fd, "(null)", 6);
		len = 6;
	}
	return (len);
}
