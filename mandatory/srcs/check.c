/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:28:59 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/26 20:50:38 by dtoure           ###   ########.fr       */
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

char	*find_path(char *envp[])
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

void	wait_all_child(t_cmd **cmds)
{
	size_t	i;
	int		status;
	t_data	*info;

	info = cmds[0]-> info;
	i = -1;
	while (cmds[++i])
	{
		if (waitpid(cmds[i]-> pid, &status, 0) < 0)
			print_err_and_exit("Error with waitpid", NULL, info, 1);
	}
	if (WIFEXITED(status))
		info -> status = WEXITSTATUS(status);
}
