/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:24:37 by pedde-so          #+#    #+#             */
/*   Updated: 2025/08/26 11:24:40 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	cont(int *pipe)
{
	(*param_factory())->fd_outfile = open((*param_factory())
			->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*param_factory())->fd_outfile == -1)
	{
		perror((*param_factory())->outfile);
		if ((*param_factory())->old_pipe_fd != -1)
			close((*param_factory())->old_pipe_fd);
		close_fds(*pipe, *(pipe + 1));
		clean();
		exit(EXIT_FAILURE);
	}
}

void	validate_files(int *pipe)
{
	if (!(*param_factory())->iteration)
	{
		(*param_factory())->fd_infile = open((*param_factory())
				->infile, O_RDONLY);
		if ((*param_factory())->fd_infile == -1)
		{
			perror((*param_factory())->infile);
			close_fds(*pipe, *(pipe + 1));
			clean();
			exit(EXIT_FAILURE);
		}
	}
	if (((*param_factory())->iteration + 1) == (*param_factory())->cmd_n)
		cont(pipe);
}
