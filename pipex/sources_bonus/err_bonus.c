/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:12:58 by rwintgen          #+#    #+#             */
/*   Updated: 2024/03/05 11:49:53 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_basic_check(int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!(argv[i][0]) || argv[i][0] == ' ')
			ft_error_msg(8);
		i++;
	}
	if (envp == NULL || envp[0] == NULL)
		ft_error_msg(7);
	if (argc < 5)
		ft_error_msg(1);
	if (access(argv[argc - 1], F_OK) == -1)
		return ;
	if (access(argv[argc - 1], R_OK | W_OK) == -1)
		ft_error_msg(3);
}

void	ft_error_msg(int err_id)
{
	if (err_id == 1)
		ft_putstr_fd("./pipex_bonus infile cmds outfile\n", 2);
	else if (err_id == 2)
		ft_putstr_fd("./pipex_bonus here_doc limiter cmds file\n", 2);
	else if (err_id == 3)
		ft_putstr_fd("pipex: insufficient permissions\n", 2);
	else if (err_id == 7)
		ft_putstr_fd("pipex: missing environment variables\n", 2);
	else if (err_id == 8)
		ft_putstr_fd("pipex: invalid command syntax\n", 2);
	exit(err_id);
}
