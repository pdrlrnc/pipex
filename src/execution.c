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

void	child(int *pipe, char **environment)
{
	char	**cmd;

	cmd = NULL;
	if (!(*param_factory())->iteration)
	{
		cmd = clean_commands(ft_split(((*param_factory())->cmds)[0], ' '));
		print_cmds(cmd);
		cmd[0] = correct_path(cmd[0]);
		if (cmd[0])
		{
			check_for_errors(dup2((*param_factory())->fd_infile, STDIN_FILENO), cmd, "dup2");
			check_for_errors(dup2(pipe[1], STDOUT_FILENO), cmd, "dup2");
			close_fds(*pipe, *(pipe + 1));
			check_for_errors(execve(cmd[0], cmd, environment), cmd, "execve");
		}
	}
	else if (((*param_factory())->iteration + 1) == (*param_factory())->cmd_n)
	{
		cmd = clean_commands(ft_split((*param_factory())->cmds[(*param_factory())->iteration], ' '));
		print_cmds(cmd);
		cmd[0] = correct_path(cmd[0]);
		if (cmd[0])
		{
			check_for_errors(dup2((*param_factory())->old_pipe_fd, STDIN_FILENO), cmd, "dup2");
			check_for_errors(dup2((*param_factory())->fd_outfile, STDOUT_FILENO), cmd, "dup2");
			close_fds(*pipe, *(pipe + 1));
			check_for_errors(execve(cmd[0], cmd, environment), cmd, "execve");
		}
	}
	else 
	{	
		cmd = clean_commands(ft_split((*param_factory())->cmds[(*param_factory())->iteration], ' '));
		print_cmds(cmd);
		cmd[0] = correct_path(cmd[0]);
		if (cmd[0])
		{
			check_for_errors(dup2((*param_factory())->old_pipe_fd, STDIN_FILENO), cmd, "dup2");
			check_for_errors(dup2(pipe[1], STDOUT_FILENO), cmd, "dup2");
			close_fds(*pipe, *(pipe + 1));
			check_for_errors(execve(cmd[0], cmd, environment), cmd, "execve");
		}
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
		check_for_errors(close((*param_factory())->fd_infile), NULL, "close");
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
		check_for_errors(close((*param_factory())->old_pipe_fd), NULL, "close");
		check_for_errors(close((*param_factory())->fd_outfile), NULL, "close");
		while (i--)
			check_for_errors(wait(&status), NULL, "wait");
	}
}

char	*correct_path(char *cmd)
{
	char	*full_path;
	int		i;
	int		access_res;

	i = 0;
	while ((*param_factory())->paths[i])
	{
		full_path = ft_strjoin((*param_factory())->paths[i++], cmd);
		if (full_path)
		{
			access_res = access(full_path, F_OK | X_OK);
			if (!access_res)
				return (full_path);
			else
				free(full_path);
		}
	}
	free(cmd);
	return (NULL);
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
