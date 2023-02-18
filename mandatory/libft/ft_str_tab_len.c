/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tab_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 20:52:39 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/13 20:48:56 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_str_tab_len(char **tab)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = -1;
	if (!tab)
		return (0);
	while (tab[++i])
		len += ft_strlen(tab[i]);
	return (len);
}
