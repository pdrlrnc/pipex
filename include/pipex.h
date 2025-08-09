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
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_params
{
	int		fd_infile;
	char	*infile;
	char	**cmds;
	int	cmd_n;
	int	iteration;
	char	*outfile;
	int		fd_outfile;
	int		old_pipe_fd;
	char	**paths;
}	t_params;

void	parse_args(int argc, char **argv, char **environment);
void	parse_environment(char **environment);
t_params	**param_factory(void);
void	clean(void);
void	clean_on_failure(int i);
void	validate_params(void);
void	check_for_malloc_failure(void *ptr);
void	clean_split(char **split);
void	validate_file_params(void);
void	child(int *pipe, char **environment);
void	parent(int *pipe);
void	check_for_errors(int res, char **cmd, char *command_name);
void	close_fds(int fd1, int fd2);
char	*correct_path(char *cmd);
char	**clean_commands(char **split);
char	*clean_quotes(char *quoted_cmd);


//functions used only for debug, they CAN'T be delivered
void	print_for_debug(void);
void	print_cmds(char **cmd);

#endif
