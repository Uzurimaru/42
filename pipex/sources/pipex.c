/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:06:55 by rwintgen          #+#    #+#             */
/*   Updated: 2024/03/06 14:49:32 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		pipe_ret;
	pid_t	pid;

	ft_basic_check(argc, argv, envp); // error mgmt function
	pipe_ret = pipe(pipefd); // pipe
	if (pipe_ret != 0) // if pipe fails
		exit(2);
	pid = fork();
	if (pid < 0) // if fork fails
		exit(3);
	if (pid == 0) 
		ft_child(argv, pipefd, envp); // exec child process
	ft_parent(argv, pipefd, envp); // exec parent process
	return (0);
}
