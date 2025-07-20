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
	printf("infile: %s\n", (*param_factory())->infile);
	while ((*param_factory())->cmds[i])
	{
		printf("param %d: %s\n", i, (*param_factory())->cmds[i]);
		i++;
	}
	printf("outfile: %s\n", (*param_factory())->outfile);
}
