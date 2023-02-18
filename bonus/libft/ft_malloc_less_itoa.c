/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_less_itoa.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:34:52 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/18 17:17:25 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nblen(long long n)
{
	int	len;

	if (n == 0)
		return (1);
	len = (n < 0);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_malloc_less_itoa(char **res, long long n)
{
	int				i;
	int				j;
	static char		str[21] = {0};

	i = (n < 0);
	j = ft_nblen(n);
	if (n < 0)
		str[0] = '-';
	str[j] = 0;
	while (--j >= i)
	{
		str[j] = (n % 10) + '0';
		n /= 10;
	}
	(*res) = str;
}
