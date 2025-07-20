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

void	child(int *fd, int *old_fd, int cmds)
{
	char	**split;

	if (cmds == (*param_factory())->cmd_n)
		dup2((*param_factory())->fd_infile, STDIN_FILENO);
	else
		dup2(*old_fd, STDIN_FILENO);
	if ((*param_factory())->cmd_n == 1)
		dup2((*param_factory())->fd_outfile, STDOUT_FILENO);
	else
		dup2(*(fd + 1), STDOUT_FILENO);

	split = ft_split((*param_factory())->cmds[(*param_factory())->cmd_n * (-1)], ' ');
	execvp(split[0], split + 1);
	clean_split(split);
}

void	parent(int *fd, int *old_fd)
{
	*old_fd = *fd;
	*(old_fd + 1) = *(fd + 1);
	close(*fd);
	close(*(fd + 1));
}
