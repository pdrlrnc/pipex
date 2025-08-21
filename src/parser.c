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
	(*param_factory())
		->infile = malloc((ft_strlen(argv[1]) + 1) * sizeof(char));
	if (!(*param_factory())->infile)
		clean_on_failure((*param_factory())->paths, NULL, NULL, NULL);
	ft_strlcpy((*param_factory())->infile, argv[1], ft_strlen(argv[1]) + 1);
	(*param_factory())->cmds = malloc((argc - 1) * sizeof(char *));
	if (!(*param_factory())->cmds)
		clean_on_failure((*param_factory())->paths, NULL, (*param_factory())
			->infile, NULL);
	i = 0;
	while ((i + 1) < (argc - 2))
		parse_args_loop(argv, &i);
	parse_args_cont(i, argc, argv);
}

void	parse_args_loop(char **argv, int *i)
{
	(*param_factory())->cmds[*i] = malloc((ft_strlen(argv[*i + 2]) + 1));
	if (!(*param_factory())->cmds[*i])
	{
		ft_splitfree_error((*param_factory())->cmds, *i);
		clean_on_failure((*param_factory())->paths, NULL, (*param_factory())
			->infile, NULL);
	}
	ft_strlcpy((*param_factory())
		->cmds[*i], argv[*i + 2], ft_strlen(argv[*i + 2]) + 1);
	(*i)++;
}

void	parse_args_cont(int i, int argc, char **argv)
{
	(*param_factory())->cmds[i] = NULL;
	(*param_factory())->cmd_n = i;
	(*param_factory())->iteration = 0;
	(*param_factory())->outfile = malloc((ft_strlen(argv[argc - 1]) + 1));
	if (!(*param_factory())->outfile)
		clean_on_failure((*param_factory())->paths, (*param_factory())
			->cmds, (*param_factory())->infile, NULL);
	ft_strlcpy((*param_factory())
		->outfile, argv[argc - 1], ft_strlen(argv[argc - 1]) + 1);
}

void	parse_environment(char **environment)
{
	int		i;

	i = 0;
	while (environment[i])
	{
		if (!ft_strncmp(environment[i++], "PATH=", 5))
			break ;
	}
	(*param_factory())->paths = ft_split(environment[--i] + 5, ':');
	if (!(*param_factory())->paths)
		free((*param_factory()));
	if (!(*param_factory())->paths)
		exit(EXIT_FAILURE);
	i = 0;
	while ((*param_factory())->paths[i])
	{
		(*param_factory())->paths[i] = ft_strdup_append(NULL, (*param_factory())
				->paths[i], "/");
		if (!(*param_factory())->paths[i++])
		{
			ft_splitfree_error((*param_factory())->paths, --i);
			free(*(param_factory()));
			exit(EXIT_FAILURE);
		}
	}
}
