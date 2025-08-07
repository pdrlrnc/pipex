/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:51:23 by pedde-so          #+#    #+#             */
/*   Updated: 2025/07/18 14:51:36 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	clean(void)
{
	free((*param_factory())->infile);
	free((*param_factory())->outfile);
	clean_split((*param_factory())->cmds);
	if ((*param_factory())->fd_infile > 0)
		close((*param_factory())->fd_infile);
	if ((*param_factory())->fd_outfile > 0)
		close((*param_factory())->fd_outfile);
	clean_split((*param_factory())->paths);
	free((*param_factory()));
}

void	check_for_malloc_failure(void *ptr)
{
	if (!ptr)
	{
		clean();
		exit(EXIT_FAILURE);
	}
}

void	clean_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	close_fds(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
	close((*param_factory())->fd_infile);
	close((*param_factory())->fd_outfile);

}
