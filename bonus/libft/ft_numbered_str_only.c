/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbered_str_only.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:13:51 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/06 21:42:12 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numbered_str_only(char *line)
{
	size_t	i;

	i = -1;
	while (line[++i])
	{
		if (!ft_isdigit(line[i]))
			return (1);
	}
	return (0);
}
