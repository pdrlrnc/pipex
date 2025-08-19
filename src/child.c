/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:40:38 by pedde-so          #+#    #+#             */
/*   Updated: 2025/08/13 17:57:05 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child(int *pipe, char **environment)
{
	char	**cmd;
	char	*full_path;

	cmd = clean_commands(ft_split(((*param_factory())
					->cmds)[(*param_factory())->iteration], ' '));
	if (!cmd || !cmd[0])
		clean_child(pipe);
	full_path = correct_path(cmd[0]);
	if (!full_path)
	{
		ft_splitfree(cmd);
		clean_child(pipe);
	}
	cmd[0] = full_path;
	if (!(*param_factory())->iteration)
		child_first_iteration(pipe, environment, cmd);
	else if (((*param_factory())->iteration + 1) == (*param_factory())->cmd_n)
		child_last_iteration(pipe, environment, cmd);
	else
		child_middle_iteration(pipe, environment, cmd);
}

void	child_first_iteration(int *pipe, char **environment, char **cmd)
{
	check_for_errors(dup2((*param_factory())
			->fd_infile, STDIN_FILENO), cmd, "dup2");
	check_for_errors(dup2(pipe[1], STDOUT_FILENO), cmd, "dup2");
	close_fds(*pipe, *(pipe + 1));
	check_for_errors(close((*param_factory())->fd_outfile), cmd, "close");
	check_for_errors(close((*param_factory())->fd_infile), cmd, "close");
	check_for_errors(execve(cmd[0], cmd, environment), cmd, cmd[0]);
}

void	child_middle_iteration(int *pipe, char **environment, char **cmd)
{
	check_for_errors(dup2((*param_factory())
			->old_pipe_fd, STDIN_FILENO), cmd, "dup2");
	check_for_errors(dup2(pipe[1], STDOUT_FILENO), cmd, "dup2");
	check_for_errors(close((*param_factory())->old_pipe_fd), cmd, "close");
	close_fds(*pipe, *(pipe + 1));
	check_for_errors(close((*param_factory())->fd_outfile), cmd, "close");
	check_for_errors(execve(cmd[0], cmd, environment), cmd, cmd[0]);
}

void	child_last_iteration(int *pipe, char **environment, char **cmd)
{
	check_for_errors(dup2((*param_factory())
			->old_pipe_fd, STDIN_FILENO), cmd, "dup2");
	check_for_errors(dup2((*param_factory())
			->fd_outfile, STDOUT_FILENO), cmd, "dup2");
	close_fds(*pipe, *(pipe + 1));
	check_for_errors(close((*param_factory())->old_pipe_fd), cmd, "close");
	check_for_errors(close((*param_factory())->fd_outfile), cmd, "close");
	check_for_errors(execve(cmd[0], cmd, environment), cmd, cmd[0]);
}
