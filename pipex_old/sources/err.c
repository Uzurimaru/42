/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:50:21 by rwintgen          #+#    #+#             */
/*   Updated: 2024/03/06 15:04:46 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_check_path(char **envp) // checks that $PATH is set
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

void	ft_err_msg(int err_id)
{
	if (err_id == 1)
		ft_putstr_fd("pipex: ./pipex infile cmd1 cmd2 outfile\n", 2);
	if (err_id == 7)
		ft_putstr_fd("pipex: missing environment variables\n", 2);
	if (err_id == 8 || err_id == 9)
		ft_putstr_fd("pipex: invalid syntax\n", 2);
	if (err_id == 6)
		ft_putstr_fd("pipex: cannot read from infile\n", 2);
	if (err_id == 10)
		ft_putstr_fd("pipex: cannot read/write on outfile\n", 2);
	if (err_id == 11)
		ft_putstr_fd("pipex: infile does not exist\n", 2);
	if (err_id == 12)
		ft_putstr_fd("pipex: could not find path\n", 2);
	if (err_id == 13)
		ft_putstr_fd("pipex: outfile is a directory\n", 2);
	if (err_id != -1)
		exit(err_id);
}

void	ft_basic_check(int argc, char **argv, char **envp)
{
	if (envp == NULL || envp[0] == NULL) // missing environment variables
		ft_err_msg(7);
	else if (argc != 5) // insufficient/too many arguments
		ft_err_msg(1);
	else if (!(argv[2][0]) || !(argv[3][0]) || !(argv[4][0])) // empty commands
		ft_err_msg(8);
	else if (argv[2][0] == ' ' || argv[3][0] == ' ') // space before commands/full space
		ft_err_msg(9);
	else if (access(argv[1], F_OK) == -1) // infile exists
		ft_err_msg(11);
	else if (access(argv[1], R_OK) == -1) // can read on infile
		ft_err_msg(6);
	else if (access(argv[4], F_OK) != -1) // outfile exists but..
	{
		if (access(argv[4], R_OK | W_OK) == -1) // cannot read or write on it
			ft_err_msg(10);
		if (open(argv[4], O_RDWR) < 0) // is not a directory
			ft_err_msg(13);
	}
	if (!(ft_check_path(envp))) // PATH enironment variable is set
		ft_err_msg(12);
}
