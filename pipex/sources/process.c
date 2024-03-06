/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:38:07 by rwintgen          #+#    #+#             */
/*   Updated: 2024/03/06 15:33:58 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exec_cmd(char *cmd, char **envp)
{
	char	*path_to_cmd;
	char	**cmd_options;

	cmd_options = ft_split(cmd, ' '); // split command
	path_to_cmd = ft_get_path(cmd_options[0], envp); // fetch $PATH variable
	if (execve(path_to_cmd, cmd_options, envp) == -1) // exec cmd
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd_options[0], 2);
		ft_free_char_tab(cmd_options);
	}
}

void	ft_parent(char **argv, int *pipefd, char **envp) // parent reads from infile and writes to pipe
{
	int		fd;

	fd = ft_open(argv[1], flag_read); // open infile with read permissions
	dup2(fd, 0); // replace stdin with infile in argv[1]
	close(fd); // close infile
	dup2(pipefd[1], 1); // replace stdout with write end of pipe
	close(pipefd[1]); // close write end of pipe
	close(pipefd[0]); // close read end of pipe
	ft_exec_cmd(argv[2], envp); // exec command taking input from infile and outputting to pipe
}

void	ft_child(char **argv, int *pipefd, char **envp) // child reads from pipe and writes to outifle
{
	int		fd;

	fd = ft_open(argv[4], flag_write); // open outfile with write permissions
	dup2(fd, 1); // replace stdout with outfile in argv[4]
	close(fd); // close outfile
	dup2(pipefd[0], 0); // replace stdin with read end of pipe
	close(pipefd[0]); // close read end of pipe
	close(pipefd[1]); // close write end of file
	ft_exec_cmd(argv[3], envp); // exec command taking input from pipe and outputting to outfile
}
