/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:57:50 by pedde-so          #+#    #+#             */
/*   Updated: 2025/07/20 13:57:51 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child(int *pipe)
{
	char	**cmd;
	int	exec_res;
	int	dup_res;

	if (!(*param_factory())->iteration)
	{
		close(pipe[0]);
		cmd = ft_split(((*param_factory())->cmds)[0], ' ');
		cmd[0] = ft_strdup_append("/bin/", cmd[0], NULL);
		dup_res = dup2((*param_factory())->fd_infile, STDIN_FILENO);
		if (dup_res == -1)
			perror("dup2");
		dup_res = dup2(pipe[1], STDOUT_FILENO);
		if (dup_res == -1)
			perror("dup2");
		exec_res = execve(cmd[0], cmd, NULL);
		if (exec_res == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
		clean_split(cmd);
	}
	else if (((*param_factory())->iteration + 1) == (*param_factory())->cmd_n)
	{
		cmd = ft_split((*param_factory())->cmds[(*param_factory())->iteration], ' ');
		cmd[0] = ft_strdup_append("/bin/", cmd[0], NULL);
		dup_res = dup2((*param_factory())->old_pipe_fd, STDIN_FILENO);
		if (dup_res == -1)
			perror("dup2");
		dup_res = dup2((*param_factory())->fd_outfile, STDOUT_FILENO);
		if (dup_res == -1)
			perror("dup2");
		execve(cmd[0], cmd, NULL);
		clean_split(cmd);
	}
	else 
	{	
		cmd = ft_split((*param_factory())->cmds[(*param_factory())->iteration], ' ');
		cmd[0] = ft_strdup_append("/bin/", cmd[0], NULL);
		dup_res = dup2((*param_factory())->old_pipe_fd, STDIN_FILENO);
		if (dup_res == -1)
			perror("dup2");
		dup2(pipe[1], STDOUT_FILENO);
		exec_res = execve(cmd[0], cmd, NULL);
		if (exec_res == -1)
			perror("execve");
		clean_split(cmd);
	}
}

void	parent(int *pipe)
{
	int	status;

	wait(&status);
	if (!(*param_factory())->iteration)
	{
		close(pipe[1]);
		(*param_factory())->old_pipe_fd = pipe[0];
	}
	else if (((*param_factory())->iteration + 1) != (*param_factory())->cmd_n)
	{
		close(pipe[1]);
		close((*param_factory())->old_pipe_fd);
		(*param_factory())->old_pipe_fd = pipe[0];
	}
}
