/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:12:51 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/08 14:12:51 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspaces(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;
	int		space;

	i = 0;
	space = 1;
	if (!s)
		return (0);
	while (s[i])
	{
		if (!ft_isspaces(s[i]))
			space = 0;
		i++;
	}
	return (i * (space == 0));
}
