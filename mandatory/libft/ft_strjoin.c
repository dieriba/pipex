/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:12:39 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/08 14:12:39 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2, char *s3, int pos_s3)
{
	size_t	tab[3];
	char	*buff;

	if (!s2)
		return (NULL);
	tab[0] = ft_strlen(s1);
	tab[1] = ft_strlen(s2);
	tab[2] = ft_strlen(s3);
	buff = calloc(sizeof(char), (tab[0] + tab[1] + tab[2] + 1));
	if (!buff)
		return (NULL);
	if (pos_s3 == 0)
	{
		ft_memcpy(buff, s1, tab[0]);
		if (s3)
			ft_memcpy(buff + tab[0], s3, tab[2]);
		ft_memcpy(buff + tab[0] + tab[2], s2, tab[1]);
		return (buff);
	}
	ft_memcpy(buff, s1, tab[0]);
	ft_memcpy(buff + tab[0], s2, tab[1]);
	if (s3)
		ft_memcpy(buff + tab[0] + tab[1], s3, tab[2] + 1);
	return (buff);
}
