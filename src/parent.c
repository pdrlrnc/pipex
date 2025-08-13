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
	int			status;
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

	if (!cmd)
		return (NULL);
	i = 0;
	while ((*param_factory())->paths[i])
	{
		full_path = ft_strjoin((*param_factory())->paths[i++], cmd);
		if (full_path)
		{
			access_res = access(full_path, F_OK | X_OK);
			if (!access_res)
			{
				free (cmd);
				return (full_path);
			}
			else
				free(full_path);
		}
	}
	return (cmd);
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
