/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:49:16 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/23 13:49:16 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	info;

	if (argc < 5)
	{
		ft_printf("Usage : %s file1 cmd1 cmd2 cmd3 ... cmdn file2\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	ft_memset(&info, 0, sizeof(t_data));
	if (!ft_strcmp(argv[1], "here_doc"))
		info.here_doc = 1;
	else
		info.here_doc = 0;
	info.doc_fd = 0;
	init_cmd(&info, argv, argc, envp);
	piping(&info, info.pipes);
	free_all(&info, info.status);
}
