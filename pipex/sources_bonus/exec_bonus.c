/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:13:29 by romain            #+#    #+#             */
/*   Updated: 2024/03/20 15:33:07 by rwintgen         ###   ########.fr       */
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

	if (!*cmd)
	{
		err_msg(ERR_CMD);
		exit(ERR_CMD);
	}
	s_cmd = ft_split(cmd, ' ');
	path_to_cmd = ft_get_path(s_cmd[0], envp);
	if (execve(path_to_cmd, s_cmd, envp) == -1)
	{
		err_msg(ERR_EXEC);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_char_tab(s_cmd);
		exit(ERR_EXEC);
	}
}

void	exec_piped_commands(char *cmd, char **envp, int *filefd, char **argv)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		err_free(filefd[0], filefd[1], argv, ERR_PIPE);
	pid = fork();
	if (pid < 0)
		err_free(filefd[0], filefd[1], argv, ERR_FORK);
	else if (pid != 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		// wait(NULL);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		close(filefd[1]);
		ft_exec_cmd(cmd, envp);
	}
}

int 
close_if_not_std(int fd) {
	if (fd != STDIN_FILENO && fd != STDOUT_FILENO) {
		return close(fd);
	}
	return (0);
}

int ft_exec_commands(int num_command,  const char *commands[], int infile_fd, int outfile_fd, const char *envp[]) {

	int i;
	int fds[2];
	int fd_in;
	int fd_out;
	
	i = 0;
	fd_in = infile_fd;
	while (i < num_command) {
		if (i < num_command - 1) {
			pipe(fds);
			fd_out = fds[1];
		} else {
			fd_out = outfile_fd;
		}
		ft_exec_command(commands[i], envp, fd_in, fd_out);
		close_if_not_std(fd_out);
		close_if_not_std(fd_in);
		fd_in = fds[0];
	}
}

int ft_exec_command(const char *cmd, const char *envp[], int fd_in, int fd_out)
{
	int pid;

	pid = fork();
	if (pid < 0) {
		return pid;
	}
	if (pid == 0) {
		return pid;
	}
	dup2(fd_in, STDIN_FILENO);
	close_if_not_std(fd_in);
	dup2(fd_out, STDOUT_FILENO);
	close_if_not_std(fd_out);
	char	**argv = ft_split(cmd, ' ');
	char const command_name = ft_find_command(argv[0], envp);
	execve(command_name, argv, envp);
	exit(-1);
	return (-1);
}

void	ft_exec_last(char *cmd, char **envp, int *filefd)
{
	dup2(filefd[1], 1);
	close(filefd[1]);
	close(filefd[0]);
	ft_exec_cmd(cmd, envp);
}
