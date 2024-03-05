/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:06:55 by rwintgen          #+#    #+#             */
/*   Updated: 2024/03/05 12:12:45 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		pipe_ret;
	pid_t	pid;

	ft_basic_check(argc, argv, envp);
	if (access(argv[4], F_OK) == -1)
		ft_open(argv[4], 1);
	if (access(argv[1], R_OK) == -1 || access(argv[4], R_OK | W_OK) == -1)
		exit(6);
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
