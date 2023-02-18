/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:28:59 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/18 21:12:41 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check(char *env, char *to_check, size_t size)
{
	size_t	i;

	i = -1;
	while ((to_check[++i] && env[++i]) && i < size && (to_check[i] == env[i]))
		;
	if (env[i] == '=' && !to_check[i])
		return (1);
	return (0);
}

char	*find_path(char **envp)
{
	size_t	i;

	if (!envp)
		return (0);
	i = -1;
	while (envp[++i])
	{
		if (envp[i][0] != 'P')
			continue ;
		if (check(envp[i], "PATH", 4))
			return (envp[i]);
	}
	return (0);
}

void	close_fd(t_data *data, int *fd, char *str)
{
	if ((*fd) > 0 && close(*fd) < 0)
	{
		(*fd) = -1;
		print_err_and_exit(str, NULL, data, 1);
	}
	(*fd) = -1;
}
