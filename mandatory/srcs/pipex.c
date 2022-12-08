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

	if (argc != 5)
	{
		ft_printf("Usage : %s 'file1' 'cmd1' 'cmd2' 'file2'\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	ft_memset(&info, 0, sizeof(t_data));
	init_cmd(&info, argv, envp);
	create_pipe(&info);
	free_all(&info, info.status);
}
