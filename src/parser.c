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

void	parse_args(int argc, char **argv, char **environment)
{
	int	i;
	
	if (argc < 5)
		exit(EXIT_FAILURE);
	parse_environment(environment);
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
	(*param_factory())->cmd_n = i;
	(*param_factory())->iteration = 0;
	(*param_factory())->outfile = malloc((ft_strlen(argv[argc - 1]) + 1) * sizeof(char));
	if (!(*param_factory())->outfile)
		return (clean_on_failure(argc - 3));
	ft_strlcpy((*param_factory())->outfile, argv[argc - 1], ft_strlen(argv[argc - 1]) + 1);
	validate_file_params();
}

void	parse_environment(char **environment)
{
	int	i;

	i = 0;
	while (environment[i])
	{
		if (!ft_strncmp(environment[i], "PATH=", 5))
			break;
		i++;
	}
	environment[i] += 5;
	(*param_factory())->paths = ft_split(environment[i], ':');
}

void	clean_on_failure(int i)
{
	while (--i > -1)
		free((*param_factory())->cmds[i]);
	free((*param_factory())->infile);
	free((*param_factory()));
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
	(*param_factory())->fd_outfile = open((*param_factory())->outfile, O_WRONLY | O_CREAT, 0644); 
	if ((*param_factory())->fd_infile == -1)
	{
		perror((*param_factory())->infile);
		clean();
		exit(EXIT_FAILURE);
	}
	print_for_debug();
}
