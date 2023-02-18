/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:15:26 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/11 18:15:26 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "stdio.h"

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
		if (!ft_isspace(s[i]))
			space = 0;
		i++;
	}
	return (i * (space == 0));
}
