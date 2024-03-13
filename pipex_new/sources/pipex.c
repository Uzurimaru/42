/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:19:12 by romain            #+#    #+#             */
/*   Updated: 2024/03/13 17:58:07 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdio.h>

// TODO leaks when does not find PATH

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		filefd[2];
	pid_t	pid[2];

	if (argc != 5)
		return (err_msg(ERR_ARGC));
	if (ft_open(argv[1], &filefd[0], FLAG_READ) < 0)
		return (err_msg(ERR_INFILE));
	if (ft_open(argv[4], &filefd[1], FLAG_WRITE) < 0)
		return (err_msg(ERR_OUTFILE));
	if (pipe(pipefd) < 0)
		return(err_msg(ERR_PIPE));
	pid[0] = fork();
	if (!pid[0])
		exec_cmd_1(argv[2], pipefd, filefd, envp);
	pid[1] = fork();
	if (!pid[1])
		exec_cmd_2(argv[3], pipefd, filefd, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	close(filefd[0]);
	close(filefd[1]);
	return(0);
}
