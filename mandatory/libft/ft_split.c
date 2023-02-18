/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:12:19 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/08 14:12:19 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_tablen(char *s, char c)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			len++;
		i = find_next_separator(s, i, c);
		if (s[i] == 0)
			break ;
		i++;
	}
	return (len);
}

static int	fill_tab(char **tab, char *s, char c, int len)
{
	int	i;
	int	j;
	int	k;
	int	m;

	i = 0;
	j = 0;
	while (i < len)
	{
		while (s[j] && s[j] == c)
			j++;
		k = j;
		k = find_end_word(s, c, k);
		tab[i] = ft_calloc(sizeof(char), (k - j + 1));
		if (!tab[i])
			return (free_all_tab_split(tab, i));
		m = 0;
		while (j < k)
			tab[i][m++] = s[j++];
		i++;
	}
	return (0);
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	int		len;

	if (!s)
		return (NULL);
	len = ft_tablen((char *)s, c);
	tab = ft_calloc(sizeof(char *), (len + 1));
	if (!tab)
		return (NULL);
	if (fill_tab(tab, s, c, len))
		return (NULL);
	return (tab);
}
