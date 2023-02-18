/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:37:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/18 22:01:14 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_here_doc(t_data *info)
{
	char		*line;
	static int	last = 1;

	while (1)
	{
		line = get_next_line(0, last);
		if (!line)
			print_err_and_exit("Error", NULL, info, 1);
		last = ft_strcmp(line, info -> limiter);
		if (!last)
			break ;
		if (write(info -> doc_pipes[1], line, ft_strlen(line)) < 0)
			print_err_and_exit("Error", NULL, info, 1);
		free(line);
	}
	get_next_line(0, last);
	free(line);
	free(info -> limiter);
	exit(0);
}

void	start_here_doc(t_data *info)
{
	int		status;
	pid_t	pid;

	status = 0;
	if (pipe(info -> doc_pipes) < 0)
		print_err_and_exit("Error", NULL, info, 0);
	pid = fork();
	if (pid == -1)
		print_err_and_exit("Error", NULL, info, 0);
	if (pid == 0)
	{
		info -> limiter = ft_strjoin(info -> limiter, "\n", 0, 0);
		if (!info -> limiter)
			print_err_and_exit("Failled to allocate memory", NULL, info, 1);
		create_here_doc(info);
	}
	close_fd(info, &info -> doc_pipes[1], "Error");
	if (waitpid(pid, &status, 0) < 0)
		print_err_and_exit("Error", NULL, info, 0);
	if (WIFSIGNALED(status))
	{
		info -> status = status + 128;
		free_all(info, info -> status);
	}
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
