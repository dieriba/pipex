/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:34:34 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/26 21:04:09 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_files(t_data *info, char *files_one, char *files_two)
{
	char	**files;

	files = ft_calloc(sizeof(char *), 3);
	if (!files)
		print_err_and_exit("Failled to allocate memory", NULL, info, 0);
	files[0] = ft_strdup(files_one);
	if (!files[0])
		print_err_and_exit("Failled to allocate memory", NULL, info, 0);
	files[1] = ft_strdup(files_two);
	if (!files[1])
		print_err_and_exit("Failled to allocate memory", NULL, info, 0);
	info -> files = files;
}

void	fill_struct(t_cmd *cmds, char *argv)
{
	char	**tab;

	tab = ft_split(argv, ' ');
	if (!tab)
		print_err_and_exit("Failled to allocate memory", NULL, cmds -> info, 0);
	cmds -> cmd = tab[0];
	cmds -> args = tab;
}

void	set_cmds_data(t_data *info, t_cmd **cmds, char *path)
{
	size_t	i;

	i = -1;
	while (++i < 2)
	{
		cmds[i]-> info = info;
		cmds[i]-> path = path;
	}
}

void	set_cmd(t_cmd *cmd, char *envp[])
{
	cmd -> args = NULL;
	cmd -> no_path = 0;
	cmd -> cmd = NULL;
	cmd -> paths = NULL;
	cmd -> envp = envp;
}

void	init_cmd(t_data *data, char **argv, char *envp[])
{
	t_cmd	**cmds;
	size_t	i;

	data -> files = NULL;
	data -> init_pipes = 0;
	i = -1;
	data -> status = 0;
	cmds = ft_calloc(sizeof(t_cmd *), 3);
	if (!cmds)
		print_err_and_exit("Failled to allocate memory", NULL, data, 0);
	data -> cmd_data = cmds;
	while (++i < 2)
	{
		cmds[i] = ft_calloc(sizeof(t_cmd), 1);
		if (!cmds[i])
			print_err_and_exit("Failled to allocate memory", NULL, data, 0);
		set_cmd(cmds[i], envp);
	}
	init_files(data, argv[1], argv[4]);
	set_cmds_data(data, data -> cmd_data, find_path(envp));
	fill_struct(cmds[0], argv[2]);
	fill_struct(cmds[1], argv[3]);
	set_path_type(cmds);
	set_path(cmds);
}
