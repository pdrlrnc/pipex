/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:59:55 by pedde-so          #+#    #+#             */
/*   Updated: 2025/07/18 10:59:58 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int 	pipe_fd[2];
	int	old_pipe_fd[2];
	int	pid;
	
	parse_args(argc, argv);
	while ((*param_factory())->cmd_n)
	{
		pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
			child(pipe_fd, old_pipe_fd, argc - 3);
		else
			parent(pipe_fd, old_pipe_fd);
		(*param_factory())->cmd_n--;
	}
}
