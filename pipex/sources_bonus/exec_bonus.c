/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:13:29 by romain            #+#    #+#             */
/*   Updated: 2024/03/18 10:37:52 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	err_free(int fd_in, int fd_out, char **argv, int err_id)
{
	close(fd_in);
	close(fd_out);
	if (!ft_strcmp(argv[1], "here_doc"))
		unlink(".heredoc_buf");
	exit(err_msg(err_id));
}

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

void	exec_piped_commands(char *cmd, char **envp, int *filefd, char **argv)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		err_free(filefd[0], filefd[1], argv, ERR_PIPE);
	if (pid < 0)
		err_free(filefd[0], filefd[1], argv, ERR_FORK);
	else if (pid != 0) // if parent
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
	}
	else
	{
		close(filefd[1]);
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		ft_exec_cmd(cmd, envp);
	}
}

void	ft_exec_last(char *cmd, char **envp, int *filefd)
{
	dup2(filefd[1], 1);
	close(filefd[1]);
	close(filefd[0]);
	ft_exec_cmd(cmd, envp);
}
