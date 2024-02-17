/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:12:58 by rwintgen          #+#    #+#             */
/*   Updated: 2024/02/16 17:26:23 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_basic_check(int argc, char **argv)
{
	if (argc < 5)
		ft_error_msg(1);
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
	exit(err_id);
}
