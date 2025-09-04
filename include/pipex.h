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
# include "printf.h"
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
	int		cmd_n;
	int		iteration;
	char	*outfile;
	int		fd_outfile;
	int		old_pipe_fd;
	char	**paths;
}	t_params;

void		parse_args(int argc, char **argv, char **environment);
void		parse_environment(char **environment);
t_params	**param_factory(void);
void		clean(void);
void		clean_on_failure(char **spt1, char **spt2, char *str1, char *str2);
void		validate_params(void);
void		check_for_malloc_failure(void *ptr);
void		clean_split(char **split);
void		child(int *pipe, char **environment);
void		parent(int *pipe);
void		check_for_errors(int res, char **cmd, char *command_name);
void		close_fds(int fd1, int fd2);
void		parent_last_iteration(int *pipe, int i);
char		*correct_path(char *cmd);
char		**clean_commands(char **split);
char		**clean_quotes(char **quoted_cmd);
int			has_closed_quotes(char *cmd);
int			has_quotes(char *cmd);
void		child_first_iteration(int *pipe, char **environment, char **cmd);
void		child_last_iteration(int *pipe, char **environment, char **cmd);
void		parse_args_cont(int i, int argc, char **argv);
char		**clean_commands_cont(char **split, int first, int last, int *i);
char		**c_q_cont(char **quoted_cmd, char **result, unsigned int *k);
void		parse_args_loop(char **argv, int *i);
char		**has_uneven_quotes(char **split, int *i);
void		child_middle_iteration(int *pipe, char **environment, char **cmd);
void		c_q_cont2(char **quoted_cmd, char **result, unsigned int *k);
char		*run_curr_dir(char *cmd);
void		clean_child(int *pipe);

#endif
