/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:13:29 by romain            #+#    #+#             */
/*   Updated: 2024/03/22 12:11:49 by rwintgen         ###   ########.fr       */
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

void	redirect_i_o(int fd_in, int fd_out)
{
	dup2(fd_in, 0);
	close(fd_in);
	dup2(fd_out, 1);
	close(fd_out);
}

int	ft_exec(t_data data, int current, int fd_in, int fd_out)
{
	pid_t	pid;
	char	*path_to_cmd;
	char	**s_cmd;

	pid = fork();
	if (pid < 0)
		err_free(data.filefd[0], data.filefd[1], data.argv, ERR_FORK);
	else if (pid != 0)
		return (0);
	if (!data.argv[current])
	{
		err_msg(ERR_CMD);
		exit(ERR_CMD);
	}
	redirect_i_o(fd_in, fd_out);
	s_cmd = ft_split(data.argv[current], ' ');
	path_to_cmd = ft_get_path(s_cmd[0], data.envp);
	if (execve(path_to_cmd, s_cmd, data.envp) == -1)
	{
		err_msg(ERR_EXEC);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_char_tab(s_cmd);
		exit(ERR_EXEC);
	}
	return (0);
}

void	exec_piped_commands(int arg_cursor, t_data data)
{
	int	pipefd[2];
	int	cmd_fd_in;
	int	cmd_fd_out;

	cmd_fd_in = data.filefd[0];
	while (++arg_cursor < data.argc - 1)
	{
		if (arg_cursor < data.argc - 2)
		{
			if (pipe(pipefd) < 0)
				err_free(data.filefd[0], data.filefd[1], data.argv, ERR_PIPE);
			cmd_fd_out = pipefd[1];
		}
		else
			cmd_fd_out = data.filefd[1];
		ft_exec(data, arg_cursor, cmd_fd_in, cmd_fd_out);
		close(cmd_fd_in);
		close(cmd_fd_out);
		cmd_fd_in = pipefd[0];
	}
}

// static void	ft_exec_cmd(char *cmd, char **envp)
// {
// 	char	*path_to_cmd;
// 	char	**s_cmd;

// 	if (!*cmd)
// 	{
// 		err_msg(ERR_CMD);
// 		exit(ERR_CMD);
// 	}
// 	s_cmd = ft_split(cmd, ' ');
// 	path_to_cmd = ft_get_path(s_cmd[0], envp);
// 	if (execve(path_to_cmd, s_cmd, envp) == -1)
// 	{
// 		err_msg(ERR_EXEC);
// 		ft_putendl_fd(s_cmd[0], 2);
// 		ft_free_char_tab(s_cmd);
// 		exit(ERR_EXEC);
// 	}
// }

// void	exec_piped_commands(char *cmd, char **envp, int *filefd, char **argv)
// {
// 	int		pipefd[2];
// 	pid_t	pid;

// 	if (pipe(pipefd) < 0)
// 		err_free(filefd[0], filefd[1], argv, ERR_PIPE);
// 	pid = fork();
// 	if (pid < 0)
// 		err_free(filefd[0], filefd[1], argv, ERR_FORK);
// 	else if (pid != 0)
// 	{
// 		close(pipefd[1]);
// 		dup2(pipefd[0], 0);
// 		close(pipefd[0]);
// 		// wait(NULL);
// 	}
// 	else
// 	{
// 		close(pipefd[0]);
// 		dup2(pipefd[1], 1);
// 		close(pipefd[1]);
// 		close(filefd[1]);
// 		ft_exec_cmd(cmd, envp);
// 	}
// }
