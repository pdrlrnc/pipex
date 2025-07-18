/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:46:03 by pedde-so          #+#    #+#             */
/*   Updated: 2025/07/18 09:46:04 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>

int	main(void)
{
	int	id;

	id = fork();
	id = fork();
	id = fork();
	id = fork();
	id = fork();
	id = fork();
	id = fork();
	id = fork();
	printf("Hello world from id: %d\n", id);


}
