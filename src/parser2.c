/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:15:17 by pedde-so          #+#    #+#             */
/*   Updated: 2025/08/13 20:15:18 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**clean_commands(char **split)
{
	int	i;

	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		if (has_quotes(split[i]) && !has_closed_quotes(split[i]))
			split = has_uneven_quotes(split, &i);
		if (!split)
		{
			clean();
			exit(EXIT_FAILURE);
		}
		i++;
	}
	split = clean_quotes(split);
	return (split);
}

char	**has_uneven_quotes(char **split, int *i)
{
	int	last;
	int	first;

	first = *i;
	split[*i] = ft_strdup_append(NULL, split[*i], " ");
	if (!split[*i])
	{
		ft_splitfree_error(split, *i);
		clean();
		exit(EXIT_FAILURE);
	}
	while (split[++(*i)])
	{
		last = *i;
		if (!has_closed_quotes(split[*i]))
			break ;
	}
	if (split[*i] && last > first)
		split = clean_commands_cont(split, first, last, i);
	return (split);
}

char	**clean_commands_cont(char **split, int first, int last, int *i)
{
	split = ft_shrink_split(split, first, last);
	if (!split)
		return (NULL);
	*i = -1;
	return (split);
}

char	**clean_quotes(char **quoted_cmd)
{
	char			**result;
	unsigned int	k;

	result = malloc((ft_splitlen(quoted_cmd) + 1) * sizeof(char *));
	if (!result)
		return (quoted_cmd);
	k = 0;
	while (quoted_cmd[k])
	{
		if (has_closed_quotes(quoted_cmd[k]))
			result = c_q_cont(quoted_cmd, result, &k);
		else
			c_q_cont2(quoted_cmd, result, &k);
		k++;
	}
	result[k] = NULL;
	ft_splitfree(quoted_cmd);
	return (result);
}

char	**c_q_cont(char **quoted_cmd, char **result, unsigned int *k)
{
	int	i;
	int	j;

	result[*k] = malloc(ft_strlen(quoted_cmd[*k])
			- has_closed_quotes(quoted_cmd[*k]) + 1);
	i = 0;
	j = 0;
	while (*(quoted_cmd[*k] + j))
	{
		while ((*(quoted_cmd[*k] + j)) == '\'')
			j++;
		if (*(quoted_cmd[*k] + j))
			*(result[*k] + i++) = *(quoted_cmd[*k] + j++);
	}
	*(result[*k] + i) = '\0';
	return (result);
}
