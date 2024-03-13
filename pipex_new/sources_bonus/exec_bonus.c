/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:13:29 by romain            #+#    #+#             */
/*   Updated: 2024/03/13 16:58:07 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	ft_exec_cmd(char *cmd, char **envp)
{
	char	*path_to_cmd;
	char	**s_cmd;

	s_cmd = ft_split(cmd, ' ');
	path_to_cmd = ft_get_path(s_cmd[0], envp);
	if (execve(path_to_cmd, s_cmd, envp) == -1)
	{
		err_msg(ERR_EXEC);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_char_tab(s_cmd);
	}
}

void	exec_piped_commands(char *cmd, char **envp, int *filefd)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		ft_printf("pipe failed\n"); //err_free_pipe close inf & outf, unlink heredoc, err_msg, exit
	pid = fork();
	if (pid < 0)
		ft_printf("fork failed\n"); // err_free_fork close inf & outf, unlink heredoc, err_msg, exit
	else if (pid != 0) // if child
	{
		close(filefd[1]);
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		ft_exec_cmd(cmd, envp);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
	}
}

void	ft_exec_last(char *cmd, char **envp, int *filefd)
{
	dup2(filefd[1], 1);
	close(filefd[1]);
	close(filefd[0]);
	ft_exec_cmd(cmd, envp);
}