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
	int	i;

	i = 0;
	free((*param_factory())->infile);
	free((*param_factory())->outfile);
	while ((*param_factory())->cmds[i])
		free((*param_factory())->cmds[i++]);
	free((*param_factory())->cmds);
	free((*param_factory()));
}
