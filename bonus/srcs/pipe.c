/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:58:19 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/30 13:35:36 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_cmd(t_cmd *cmd)
{
	size_t	i;

	i = -1;
	if (cmd -> no_path)
	{
		while (cmd -> paths[++i])
		{
			if (access(cmd -> paths[i], X_OK) != -1)
				execve(cmd -> paths[i], cmd -> args, cmd -> envp);
		}
		print_err_and_exit("bash: ", cmd, cmd -> info, 1);
	}
	else
	{
		if (access(cmd -> cmd, X_OK) != -1)
			execve(cmd -> cmd, cmd -> args, cmd -> envp);
		print_err_and_exit("bash: ", cmd, cmd -> info, 1);
	}
}

void	start(t_cmd *cmd, int pipes[2])
{
	char	*file;
	int		fd;

	file = cmd -> info -> files[0];
	if (access(file, F_OK | R_OK) < 0)
		print_err_and_exit("bash ", cmd, cmd -> info, 1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_err_and_exit("bash ", cmd, cmd -> info, 1);
	if (dup2(fd, STDIN_FILENO) < 0)
		print_err_and_exit("bash ", cmd, cmd -> info, 1);
	if (close(fd) < 0)
		print_err_and_exit("bash ", cmd, cmd -> info, 1);
	if (cmd -> info -> here_doc && unlink("here_doc") < 0)
		print_err_and_exit("bash ", cmd, cmd -> info, 1);
	if (dup2(pipes[1], STDOUT_FILENO) < 0)
		print_err_and_exit("bash ", cmd, cmd -> info, 1);
	if (close(pipes[1]) < 0 || close(pipes[0]))
		print_err_and_exit("bash ", cmd, cmd -> info, 1);
	cmd -> inited = 0;
	run_cmd(cmd);
}

void	end(t_cmd *cmd, int pipes[2], int prev_pipes)
{
	char	*file;
	int		fd;
	int		flags;

	if (cmd -> info -> here_doc)
		flags = O_RDWR | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	file = cmd -> info -> files[1];
	fd = open(file, flags, 0666);
	if (access(file, W_OK) < 0)
		print_err_and_exit("bash ", cmd, cmd -> info, 1);
	if (fd < 0)
		print_err_and_exit("bash ", cmd, cmd -> info, 1);
	if (dup2(prev_pipes, STDIN_FILENO) < 0)
		print_err_and_exit("bash ", cmd, cmd -> info, 1);
	if (close(pipes[0]) < 0 || close(pipes[1]) < 0)
		print_err_and_exit("bash ", cmd, cmd -> info, 1);
	cmd -> inited = 0;
	if (dup2(fd, STDOUT_FILENO) < 0)
		print_err_and_exit("bash ", cmd, cmd -> info, 1);
	if (close(fd) < 0 || close(prev_pipes) < 0)
		print_err_and_exit("bash ", cmd, cmd -> info, 1);
	cmd -> info -> prev_pipes = -1;
	run_cmd(cmd);
}

void	forking(t_data *data, int pipes[2], int i)
{
	t_cmd	**cmds;

	cmds = data -> cmd_data;
	cmds[i]-> inited = 1;
	if (i == 0)
		start(data -> cmd_data[0], pipes);
	else if (i == data -> num_cmds - 1)
		end(cmds[i], pipes, data -> prev_pipes);
	else
	{
		if (data -> prev_pipes != -1)
		{
			if (dup2(data -> prev_pipes, STDIN_FILENO) < 0)
				print_err_and_exit("bash ", NULL, cmds[i]-> info, 1);
			if (close(data -> prev_pipes) < 0)
				print_err_and_exit("bash ", NULL, cmds[i]-> info, 1);
			data -> prev_pipes = -1;
		}
		if (dup2(pipes[1], STDOUT_FILENO) < 0)
			print_err_and_exit("bash ", NULL, cmds[i]-> info, 1);
		if (close(pipes[1]) < 0 || close(pipes[0]) < 0)
			print_err_and_exit("bash ", NULL, cmds[i]-> info, 1);
		cmds[i]-> inited = 0;
		run_cmd(cmds[i]);
	}
}

void	piping(t_data	*data, int pipes[2])
{
	int		i;
	t_cmd	**cmds;
	pid_t	pid_ret;

	cmds = data -> cmd_data;
	i = -1;
	while (cmds[++i])
	{
		if (pipe(pipes) < 0)
			print_err_and_exit("bash", NULL, data, 1);
		pid_ret = fork();
		if (pid_ret < 0)
			print_err_and_exit("bash", NULL, data, 1);
		if (pid_ret)
			close_fd(data, data -> pipes[1], "bash");
		if (pid_ret == 0)
			forking(data, pipes, i);
		if (data -> prev_pipes != -1)
			close_fd(data, data -> prev_pipes, "bash");
		data -> prev_pipes = pipes[0];
		cmds[i]-> pid = pid_ret;
	}
	close_fd(data, data -> prev_pipes, "bash");
	wait_all_child(cmds);
}
