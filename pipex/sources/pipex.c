/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:06:55 by rwintgen          #+#    #+#             */
/*   Updated: 2024/02/16 15:58:11 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		pipe_ret;
	pid_t	pid;

	if (argc != 5)
	{
		ft_putstr_fd("./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(1);
	}
	if (access(argv[1], R_OK) == -1 || access(argv[4], R_OK | W_OK) == -1)
		exit(11);
	pipe_ret = pipe(pipefd);
	if (pipe_ret != 0)
		exit(2);
	pid = fork();
	if (pid < 0)
		exit(3);
	if (pid == 0)
		ft_child(argv, pipefd, envp);
	ft_parent(argv, pipefd, envp);
	return (0);
}
