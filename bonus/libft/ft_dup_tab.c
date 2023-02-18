/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:16:59 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/18 22:11:01 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**set_null_tab(char **tabs, char **tab, char *to_join)
{
	(*tab) = ft_strjoin(NULL, to_join, 0, 0);
	if ((*tab) == NULL)
		return (NULL);
	return (tabs);
}

char	**ft_dup_tab(char **to_copy, char *to_join)
{
	size_t	i;
	char	**tab;

	if (!to_join)
		return (NULL);
	i = ft_tab_len(to_copy) + (to_copy == NULL);
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	if (to_copy == NULL)
		return (set_null_tab(tab, &tab[0], to_join));
	tab[i] = 0;
	i = -1;
	while (to_copy[++i])
	{
		tab[i] = ft_strjoin(to_copy[i], to_join, 0, 0);
		if (!tab[i])
			return (ft_free_tab(tab));
	}
	ft_free_tab(to_copy);
	return (tab);
}
