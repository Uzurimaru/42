/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:12:58 by rwintgen          #+#    #+#             */
/*   Updated: 2024/03/06 15:20:17 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	ft_check_path(char **envp)
{
	int		i;
	int		j;
	char	*envp_name;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=' && envp[i][j])
			j++;
		envp_name = ft_substr(envp[i], 0, j);
		if (!(ft_strcmp(envp_name, "PATH")))
		{
			free(envp_name);
			return (1);
		}
		free(envp_name);
		i++;
	}
	return (0);
}

void	ft_error_msg(int err_id)
{
	if (err_id == 1)
		ft_putstr_fd("./pipex_bonus infile cmds outfile\n", 2);
	if (err_id == 2)
		ft_putstr_fd("./pipex_bonus here_doc limiter cmds file\n", 2);
	if (err_id == 3)
		ft_putstr_fd("pipex: cannot read/write on outfile\n", 2);
	if (err_id == 7)
		ft_putstr_fd("pipex: missing environment variables\n", 2);
	if (err_id == 8)
		ft_putstr_fd("pipex: invalid syntax\n", 2);
	if (err_id == 9)
		ft_putstr_fd("pipex: outfile is a directory\n", 2);
	if (err_id == 10)
		ft_putstr_fd("pipex: could not find path\n", 2);
	if (err_id == 11)
		ft_putstr_fd("pipex: infile does not exist\n", 2);
	exit(err_id);
}

void	ft_basic_check(int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!(argv[i][0]) || argv[i][0] == ' ') // No empty arguments...
			ft_error_msg(8);
		if (++i == 2 && ft_strcmp("here_doc", argv[1]) == 0) // except heredoc limiter
			i++;
		// TODO fix empty heredoc limiter
	}
	if (ft_strcmp("here_doc", argv[1]) != 0 && access(argv[1], F_OK) == -1) // first argument is an infile and exists
		ft_error_msg(11);
	if (envp == NULL || envp[0] == NULL) // missing environment variables
		ft_error_msg(7);
	else if (argc < 5) // insufficient arguments
		ft_error_msg(1);
	else if (access(argv[argc - 1], F_OK) != -1) // outfile exists but...
	{
		if (access(argv[argc - 1], R_OK | W_OK) == -1) // cannot read or write on it
			ft_error_msg(3);
		else if (open(argv[argc - 1], O_RDWR) < 0) // file is not a directory
			ft_error_msg(9);
	}
	else if (!(ft_check_path(envp))) // PATH enironment variable is set
	ft_error_msg(10);
}
