/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:37:31 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/27 17:40:54 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*create_file(t_data *info)
{
	char		*line;
	static int	last = 1;

	info -> doc_fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC);
	if (info -> doc_fd < 0)
		print_err_and_exit("Error", NULL, info, 1);
	while (1)
	{
		line = get_next_line(0, last);
		if (!line)
			print_err_and_exit("Error", NULL, info, 1);
		last = ft_strcmp(line, info -> limiter);
		if (!last)
			break ;
		if (write(info -> doc_fd, line, ft_strlen(line)) < 0)
			print_err_and_exit("Error", NULL, info, 1);
		free(line);
	}
	get_next_line(0, last);
	free(line);
	free(info -> limiter);
	if (close(info -> doc_fd) < 0)
		print_err_and_exit("Error", NULL, info, 1);
	info -> doc_fd = 0;
	return ("here_doc");
}

char	*start_here_doc(t_data *info)
{
	char	*file;

	info -> limiter = ft_strjoin(info -> limiter, "\n");
	if (!info -> limiter)
		print_err_and_exit("Failled to allocate memory", NULL, info, 1);
	file = create_file(info);
	if (!file)
		print_err_and_exit("Failled to allocate memory", NULL, info, 1);
	return (file);
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
