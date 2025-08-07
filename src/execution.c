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

	cmd = NULL;
	if (!(*param_factory())->iteration)
	{
		check_for_errors(close(pipe[0]), cmd, "close");
		cmd = ft_split(((*param_factory())->cmds)[0], ' ');
		cmd[0] = ft_strdup_append("/bin/", cmd[0], NULL);
		check_for_errors(dup2((*param_factory())->fd_infile, STDIN_FILENO), cmd, "dup2");
		check_for_errors(dup2(pipe[1], STDOUT_FILENO), cmd, "dup2");
		check_for_errors(execve(cmd[0], cmd, NULL), cmd, "execve");
	}
	else if (((*param_factory())->iteration + 1) == (*param_factory())->cmd_n)
	{
		cmd = ft_split((*param_factory())->cmds[(*param_factory())->iteration], ' ');
		cmd[0] = ft_strdup_append("/bin/", cmd[0], NULL);
		check_for_errors(dup2((*param_factory())->old_pipe_fd, STDIN_FILENO), cmd, "dup2");
		check_for_errors(dup2((*param_factory())->fd_outfile, STDOUT_FILENO), cmd, "dup2");
		check_for_errors(execve(cmd[0], cmd, NULL), cmd, "execve");
	}
	else 
	{	
		cmd = ft_split((*param_factory())->cmds[(*param_factory())->iteration], ' ');
		cmd[0] = ft_strdup_append("/bin/", cmd[0], NULL);
		check_for_errors(dup2((*param_factory())->old_pipe_fd, STDIN_FILENO), cmd, "dup2");
		check_for_errors(dup2(pipe[1], STDOUT_FILENO), cmd, "dup2");
		check_for_errors(execve(cmd[0], cmd, NULL), cmd, "execve");
	}
}

void	parent(int *pipe)
{
	int	status;
	static int	i;

	i++;
	if (!(*param_factory())->iteration)
	{
		check_for_errors(close(pipe[1]), NULL, "close");
		(*param_factory())->old_pipe_fd = pipe[0];
	}
	else if (((*param_factory())->iteration + 1) != (*param_factory())->cmd_n)
	{
		check_for_errors(close(pipe[1]), NULL, "close");
		check_for_errors(close((*param_factory())->old_pipe_fd), NULL, "close");
		(*param_factory())->old_pipe_fd = pipe[0];
	}
	else 
	{
		check_for_errors(close(pipe[0]), NULL, "close");
		check_for_errors(close(pipe[1]), NULL, "close");
		while (i--)
			check_for_errors(wait(&status), NULL, "wait");
	}
}

void	check_for_errors(int res, char **cmd, char *command_name)
{
	if (res == -1)
	{
		perror(command_name);
		if (cmd)
			clean_split(cmd);
		exit(EXIT_FAILURE);
	}
}
