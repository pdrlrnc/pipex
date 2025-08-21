/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:24:02 by pedde-so          #+#    #+#             */
/*   Updated: 2025/08/13 20:24:04 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	parent(int *pipe)
{
	static int	i;

	i++;
	if (!(*param_factory())->iteration)
	{
		check_for_errors(close(pipe[1]), NULL, "close");
		if ((*param_factory())->fd_infile != -1)
			check_for_errors(close((*param_factory())
					->fd_infile), NULL, "close");
		(*param_factory())->old_pipe_fd = pipe[0];
	}
	else if (((*param_factory())->iteration + 1) != (*param_factory())->cmd_n)
	{
		check_for_errors(close(pipe[1]), NULL, "close");
		if ((*param_factory())->old_pipe_fd != -1)
			check_for_errors(close((*param_factory())
					->old_pipe_fd), NULL, "close");
		(*param_factory())->old_pipe_fd = pipe[0];
	}
	else
		parent_last_iteration(pipe, i);
}

void	parent_last_iteration(int *pipe, int i)
{
	int	status;

	check_for_errors(close(pipe[0]), NULL, "close");
	check_for_errors(close(pipe[1]), NULL, "close");
	if ((*param_factory())->old_pipe_fd != -1)
		check_for_errors(close((*param_factory())->old_pipe_fd), NULL, "close");
	if ((*param_factory())->fd_outfile != -1)
		check_for_errors(close((*param_factory())->fd_outfile), NULL, "close");
	while (i--)
		check_for_errors(wait(&status), NULL, "wait");
}

void	check_for_errors(int res, char **cmd, char *command_name)
{
	if (res == -1)
	{
		perror(command_name);
		if (cmd)
			ft_splitfree(cmd);
		clean();
		exit(EXIT_FAILURE);
	}
}
