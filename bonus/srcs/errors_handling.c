/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:31:37 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/18 21:39:31 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmd(t_cmd **cmd)
{
	size_t	i;

	if (!cmd)
		return ;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]-> cmd && cmd[i]-> no_path)
			free(cmd[i]-> cmd);
		if (cmd[i]-> args)
			ft_free_tab(cmd[i]-> args);
		if (cmd[i]-> paths)
			ft_free_tab(cmd[i]-> paths);
		free(cmd[i]);
	}
	free(cmd);
}

void	free_files(char **files)
{
	size_t	i;

	i = -1;
	if (!files)
		return ;
	while (++i < 2)
		free(files[i]);
	free(files);
}

void	free_all(t_data *to_free, int code)
{
	free_files(to_free -> files);
	free_cmd(to_free -> cmd_data);
	if (to_free -> end_fd == -1)
		code = 1;
	exit(code);
}

void	print_err(char *str, t_cmd *cmd, int type)
{
	t_data	*info;

	info = cmd -> info;
	if (errno == 2 && cmd && cmd -> no_path && !cmd -> inited)
	{
		ft_putstr_fd("bash: command not found: ", 2);
		ft_putstr_fd(cmd -> args[0], 2);
		ft_putchar_fd('\n', 2);
		info -> status = 127;
	}
	else if (errno == 2 && cmd && !cmd -> no_path && !cmd -> inited)
	{
		ft_putstr_fd("bash: no such file or directory: ", 2);
		ft_putstr_fd(cmd -> cmd, 2);
		ft_putchar_fd('\n', 2);
		info -> status = 127;
	}
	else if (type)
		perror(str);
	else
	{
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
	}
	errno = 0;
}

void	print_err_and_exit(char *str, t_cmd *cmd, t_data *info, int type)
{
	if (cmd)
		print_err(str, cmd, type);
	if (info -> prev_pipes != -1)
		if (close(info -> prev_pipes) < 0)
			perror("Error");
	if (info -> here_doc && info -> doc_pipes[0] > 0)
		close(info -> doc_pipes[0]);
	if (info -> here_doc && info -> doc_pipes[1] > 0)
		close(info -> doc_pipes[1]);
	if ((cmd && cmd -> inited) && info -> pipes[0] > 0)
		close(info -> pipes[0]);
	if ((cmd && cmd -> inited) && info -> pipes[1] > 0)
		close(info -> pipes[1]);
	if (errno)
		perror(NULL);
	free_all(info, info -> status);
}
