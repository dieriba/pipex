/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:44:54 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/27 17:46:38 by dtoure           ###   ########.fr       */
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

void	start(t_cmd *cmd, int pipes[2], char *files)
{
	int	fd;

	if (access(files, F_OK | R_OK) < 0)
		print_err_and_exit("bash: ", NULL, cmd -> info, 1);
	fd = open(files, O_RDONLY);
	if (fd < 0)
		print_err_and_exit("bash: ", NULL, cmd -> info, 1);
	if (dup2(fd, STDIN_FILENO) < 0)
		print_err_and_exit("bash: ", NULL, cmd -> info, 1);
	if (close(fd) < 0)
		print_err_and_exit("bash: ", NULL, cmd -> info, 1);
	if (dup2(pipes[1], STDOUT_FILENO) < 0)
		print_err_and_exit("bash: ", NULL, cmd -> info, 1);
	if (close(pipes[1]) < 0 || close(pipes[0]) < 0)
		print_err_and_exit("bash: ", NULL, cmd -> info, 1);
	run_cmd(cmd);
}

void	end(t_cmd *cmd, int pipes[2], char *files)
{
	int		fd;

	fd = open(files, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (access(files, W_OK) < 0)
		print_err_and_exit("bash: ", NULL, cmd -> info, 1);
	if (fd < 0)
		print_err_and_exit("bash: ", NULL, cmd -> info, 1);
	if (dup2(pipes[0], STDIN_FILENO) < 0)
		print_err_and_exit("bash: ", NULL, cmd -> info, 1);
	if (close(pipes[1]) < 0 || close(pipes[0]) < 0)
		print_err_and_exit("bash: ", NULL, cmd -> info, 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		print_err_and_exit("bash: ", NULL, cmd -> info, 1);
	if (close(fd) < 0)
		print_err_and_exit("bash: ", NULL, cmd -> info, 1);
	run_cmd(cmd);
}

void	create_pipe(t_data *data)
{
	char	**files;
	int		pid_ret;

	files = data -> files;
	if (pipe(data -> pipes) < 0)
		print_err_and_exit("bash: ", NULL, data, 1);
	data -> init_pipes = 1;
	pid_ret = fork();
	if (pid_ret < 0)
		print_err_and_exit("bash: ", NULL, data, 1);
	data -> cmd_data[0]-> pid = pid_ret;
	if (pid_ret == 0)
		start(data -> cmd_data[0], data -> pipes, files[0]);
	pid_ret = fork();
	if (pid_ret < 0)
		print_err_and_exit("bash: ", NULL, data, 1);
	data -> cmd_data[1]-> pid = pid_ret;
	if (pid_ret == 0)
		end(data -> cmd_data[1], data -> pipes, files[1]);
	if (close(data -> pipes[1]) < 0 || close(data -> pipes[0]) < 0)
		print_err_and_exit("bash: ", NULL, data, 1);
	wait_all_child(data -> cmd_data);
}
