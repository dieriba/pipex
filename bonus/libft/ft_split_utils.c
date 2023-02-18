/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:42:29 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/14 17:21:34 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	skip_split(char *to_parse, size_t *i, int quote)
{
	size_t	j;

	j = (*i);
	while (1)
	{
		while (to_parse[++j])
		{
			if ((to_parse[j] == quote && to_parse[j] == '"')
				&& valid_double_split(to_parse, j))
				break ;
			else if (to_parse[j] == quote && to_parse[j] == '\'')
				break ;
		}
		if (to_parse[j] == 0 || to_parse[j + 1] == 0)
			break ;
		else if (to_parse[j + 1] == '\'' || to_parse[j + 1] == '"')
			quote = to_parse[++j];
	}
	(*i) = j;
}

int	valid_double_split(char const *s, size_t i)
{
	if ((i > 0 && s[i - 1] != '\\') || i == 0)
		return (1);
	return (0);
}

size_t	find_next_separator(char *to_parse, size_t i, char c)
{
	while (to_parse[i])
	{
		if ((to_parse[i] == '"' && valid_double_split(to_parse, i))
			|| to_parse[i] == '\'')
			skip_split(to_parse, &i, to_parse[i]);
		else if (to_parse[i] == c)
			break ;
		if (to_parse[i] == 0)
			break ;
		i++;
	}
	return (--i);
}

int	find_end_word(char *s, char c, size_t k)
{
	while (s[k] && s[k] != c)
	{
		if ((s[k] == '"' && valid_double_split(s, k)) || s[k] == '\'')
			skip_split(s, &k, s[k]);
		if (s[k] == 0)
			break ;
		k++;
	}
	return (k);
}

int	free_all_tab_split(char **tab, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		free(tab[i]);
	free(tab);
	return (1);
}
