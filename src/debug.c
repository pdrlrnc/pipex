/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 11:59:27 by pedde-so          #+#    #+#             */
/*   Updated: 2025/07/20 11:59:43 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>

void	print_for_debug(void)
{
	int	i;

	i = 0;
	printf("infile (fd=%d): %s\n", (*param_factory())->fd_infile, (*param_factory())->infile);
	while ((*param_factory())->cmds[i])
	{
		printf("param %d: %s\n", i, (*param_factory())->cmds[i]);
		i++;
	}
	printf("outfile (fd=%d): %s\n", (*param_factory())->fd_outfile ,(*param_factory())->outfile);

	printf("cmds_n = %d\n", (*param_factory())->cmd_n);

	printf("paths = \n");
	i = 0;
	while ((*param_factory())->paths[i])
		printf("%s\n", (*param_factory())->paths[i++]);
}

void	print_cmds(char **cmd)
{
	int	i;

	printf("Printing commands:\n");
	i = 0;
	while (cmd[i])
	{
		printf("cmd[%d]: %s\n", i, cmd[i]);
		i++;
	}
}
