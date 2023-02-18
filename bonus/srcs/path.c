/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:41:48 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/18 22:09:47 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_path(t_cmd *cmd)
{
	char	**tab;
	char	*path;

	path = NULL;
	if (cmd -> path)
		path = cmd -> path + 5;
	cmd -> paths = ft_split(path, ':');
	if (!cmd -> paths && cmd -> path)
		print_err_and_exit("Failled to allocate memory", NULL, cmd -> info, 0);
	tab = ft_dup_tab(cmd -> paths, cmd -> cmd);
	if (!tab)
		print_err_and_exit("Failled to allocate memory", NULL, cmd -> info, 0);
	cmd -> paths = tab;
}

void	set_path(t_cmd **cmds)
{
	size_t	i;

	i = -1;
	while (cmds[++i])
	{
		if (cmds[i]-> no_path)
			create_path(cmds[i]);
	}
}

void	set_path_type(t_cmd **cmds)
{
	size_t	i;
	char	*cmd;

	i = -1;
	while (cmds[++i])
	{
		if (!ft_strchr(cmds[i]-> cmd, '/') || !cmds[i]-> cmd)
		{
			if (!cmds[i]-> cmd)
				cmd = "''";
			else
				cmd = cmds[i]-> cmd;
			cmds[i]-> no_path = 1;
			cmds[i]-> cmd = ft_strjoin("/", cmd, 0, 0);
			if (!cmds[i]-> cmd)
				print_err_and_exit("Failled to allocate memory", NULL,
					cmds[0]-> info, 0);
		}
	}		
}
