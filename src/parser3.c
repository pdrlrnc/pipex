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
