/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factories.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:57:20 by pedde-so          #+#    #+#             */
/*   Updated: 2025/07/18 10:57:22 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_params	**param_factory(void)
{
	static	t_params *params;

	if (!params)
	{
		params = malloc(sizeof(t_params));
		if (!params)
			exit(EXIT_FAILURE);
	}
	return (&params);
}
