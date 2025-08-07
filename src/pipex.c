/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:59:55 by pedde-so          #+#    #+#             */
/*   Updated: 2025/07/18 10:59:58 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv)
{
	int 	pipefd[2];
	int	pid;
	
	parse_args(argc, argv);
	while ((*param_factory())->iteration < (*param_factory())->cmd_n)
	{
		check_for_errors(pipe(pipefd), NULL, "pipe");
		pid = fork();
		if (pid == 0)
			child(pipefd);
		else if (pid != -1)
			parent(pipefd);
		if (pid == -1)
			check_for_errors(-1, NULL, "fork");
		(*param_factory())->iteration++;
	}
}
