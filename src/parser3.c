/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 22:49:38 by pedde-so          #+#    #+#             */
/*   Updated: 2025/08/13 22:49:43 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	has_quotes(char *cmd)
{
	int	i;

	i = 0;
	while (*(cmd + i))
	{
		if (*(cmd + i) == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	has_closed_quotes(char *cmd)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (*(cmd + i))
	{
		if (*(cmd + i) == '\'')
			quotes++;
		i++;
	}
	if (quotes % 2 == 0)
		return (quotes);
	return (0);
}

char	*correct_path(char *cmd)
{
	char	*full_path;
	int		i;
	int		access_res;

	if (!cmd)
		return (NULL);
	i = 0;
	full_path = ft_strchr(cmd, '/');
	if (full_path)
		return (run_curr_dir(cmd));
	while ((*param_factory())->paths[i])
	{
		full_path = ft_strjoin((*param_factory())->paths[i++], cmd);
		if (full_path)
		{
			access_res = access(full_path, F_OK | X_OK);
			if (!access_res)
				free (cmd);
			if (!access_res)
				return (full_path);
			else
				free(full_path);
		}
	}
	return (NULL);
}

char	*run_curr_dir(char *cmd)
{
	int	access_res;

	access_res = access(cmd, F_OK | X_OK);
	if (errno == EACCES)
	{
		ft_printf("%s: Permission denied\n", cmd);
		return (NULL);
	}
	else if (errno == ENOENT)
	{
		ft_printf("%s: No such file or directory\n", cmd);
		return (NULL);
	}
	return (ft_strdup(cmd));
}

void	c_q_cont2(char **quoted_cmd, char **result, unsigned int *k)
{
	result[*k] = malloc(ft_strlen(quoted_cmd[*k]) + 1);
	if (!result[*k])
	{
		ft_splitfree_error(result, *k);
		ft_splitfree(quoted_cmd);
		clean();
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(result[*k], quoted_cmd[*k], ft_strlen(quoted_cmd[*k]) + 1);
}
