/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:51:44 by pedde-so          #+#    #+#             */
/*   Updated: 2025/07/18 10:51:45 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	parse_args(int argc, char **argv)
{
	int	i;
	
	if (argc < 5)
		exit(EXIT_FAILURE);
	(*param_factory())->infile = malloc((ft_strlen(argv[1]) + 1) * sizeof(char));
	if (!(*param_factory())->infile)
	{
		free((*param_factory()));
		exit(EXIT_FAILURE);
	}
	ft_strlcpy((*param_factory())->infile, argv[1], ft_strlen(argv[1]) + 1);
	(*param_factory())->cmds = malloc((argc - 1) * sizeof(char *));
	i = 0;
	while ((i + 1) < (argc - 2))
	{
		(*param_factory())->cmds[i] = malloc((ft_strlen(argv[i + 2]) + 1) * sizeof(char));
		if (!(*param_factory())->cmds[i])
			return (clean_on_failure(i));
		ft_strlcpy((*param_factory())->cmds[i], argv[i + 2], ft_strlen(argv[i + 2]) + 1);
		i++;
	}
	(*param_factory())->cmds[i] = NULL;
	(*param_factory())->outfile = malloc((ft_strlen(argv[argc - 1]) + 1) * sizeof(char));
	if (!(*param_factory())->outfile)
		return (clean_on_failure(argc - 3));
	ft_strlcpy((*param_factory())->outfile, argv[argc - 1], ft_strlen(argv[argc - 1]) + 1);
	validate_params();
}

void	clean_on_failure(int i)
{
	while (--i > -1)
		free((*param_factory())->cmds[i]);
	free((*param_factory())->infile);
	free((*param_factory()));
}

void	validate_params(void)
{
	int	access_res;
	char	*path;
	char	**split_res;
	int	i;
	
	access_res = 0;
	i = 0;
	while (access_res == 0 && (*param_factory())->cmds[i] != NULL)
	{
		split_res = ft_split((*param_factory())->cmds[i++], ' ');
		check_for_malloc_failure(split_res);
		path = ft_strjoin("/usr/bin/", split_res[0]);
		check_for_malloc_failure(path);
		access_res = (access(path , F_OK | X_OK));
		if (access_res == -1)
			perror(split_res[0]);
		free(path);
		clean_split(split_res);
	}
	(*param_factory())->cmd_n = i;
	(*param_factory())->iteration = 0;
	if (access_res == -1)
		exit(EXIT_FAILURE);
	validate_file_params();
}

void	validate_file_params(void)
{
	(*param_factory())->fd_infile = open((*param_factory())->infile, O_RDONLY);
	if ((*param_factory())->fd_infile == -1)
	{
		perror((*param_factory())->infile);
		clean();
		exit(EXIT_FAILURE);
	}
	(*param_factory())->fd_outfile = open((*param_factory())->outfile, O_CREAT, 0644); 
	if ((*param_factory())->fd_infile == -1)
	{
		perror((*param_factory())->infile);
		clean();
		exit(EXIT_FAILURE);
	}
	print_for_debug();
}
