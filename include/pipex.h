/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:46:22 by pedde-so          #+#    #+#             */
/*   Updated: 2025/07/18 09:46:23 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <errno.h>
# include <stdio.h>

typedef struct s_params
{
	char	*infile;
	char	**cmds;
	char	*outfile;
}	t_params;

void	parse_args(int argc, char **argv);
t_params	**param_factory(void);
void	clean(void);
void	clean_on_failure(int i);
void	validate_params(void);
void	check_for_malloc_failure(void *ptr);
void	clean_split(char **split);


//functions used only for debug, they CAN'T be delivered
void	print_for_debug(void);

#endif
