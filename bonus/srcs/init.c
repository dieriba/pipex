/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:34:34 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/27 17:17:24 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_files(t_data *info, char *files_one, char *files_two)
{
	size_t	i;
	char	*file;

	i = -1;
	file = files_one;
	info -> files = ft_calloc(sizeof(char *), 2);
	if (!info -> files)
		print_err_and_exit("Failed to allocate memory", NULL, info, 1);
	while (++i < 2)
	{
		if (info -> here_doc && i == 0)
			file = start_here_doc(info);
		else if (i == 1)
			file = files_two;
		info -> files[i] = ft_strdup(file);
		if (!info -> files[i])
			print_err_and_exit("Failed to allocate memory", NULL, info, 0);
	}
}

void	fill_struct(t_cmd **cmds, char **argv)
{
	char	**tab;
	size_t	i;
	size_t	j;

	j = -1 + 2 + (cmds[0]-> info -> here_doc == 1) + 1;
	i = -1;
	while (cmds[++i])
	{
		tab = ft_split(argv[j + i], ' ');
		if (!tab)
			print_err_and_exit("Failed to allocate memory",
				NULL, cmds[0]-> info, 0);
		cmds[i]-> cmd = tab[0];
		cmds[i]-> args = tab;
	}
}

void	set_cmds_data(t_data *info, t_cmd **cmds, char *path)
{
	int	i;

	i = -1;
	while (++i < info -> num_cmds)
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
	cmd -> inited = 0;
	cmd -> read_end = 0;
	cmd -> write_end = 0;
}

void	init_cmd(t_data *info, char **argv, int argc, char **envp)
{
	t_cmd	**cmds;
	int		i;

	info -> files = NULL;
	info -> num_cmds = argc - 3 - (info -> here_doc == 1);
	info -> prev_pipes = -1;
	info -> limiter = argv[2];
	info -> status = 0;
	i = -1;
	cmds = ft_calloc(sizeof(t_cmd *), info -> num_cmds + 1);
	if (!cmds)
		print_err_and_exit("Failed to allocate memory", NULL, info, 0);
	info -> cmd_data = cmds;
	while (++i < info -> num_cmds)
	{
		cmds[i] = malloc(sizeof(t_cmd));
		if (!cmds[i])
			print_err_and_exit("Failed to allocate memory", NULL, info, 0);
		set_cmd(cmds[i], envp);
	}
	init_files(info, argv[1], argv[argc - 1]);
	set_cmds_data(info, info -> cmd_data, find_path(envp));
	fill_struct(cmds, argv);
	set_path_type(cmds);
	set_path(cmds);
}
