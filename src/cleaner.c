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
	ft_splitfree((*param_factory())->cmds);
	ft_splitfree((*param_factory())->paths);
	close((*param_factory())->fd_infile);
	close((*param_factory())->fd_outfile);
	free((*param_factory()));
}

void	close_fds(int fd1, int fd2)
{
	check_for_errors(close(fd1), NULL, "close");
	check_for_errors(close(fd2), NULL, "close");
}

void	clean_on_failure(char **split1, char **split2, char *str1, char *str2)
{
	if (split1)
		ft_splitfree(split1);
	if (split2)
		ft_splitfree(split2);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	free((*param_factory()));
	exit(EXIT_FAILURE);
}
