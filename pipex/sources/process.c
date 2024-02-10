/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:38:07 by rwintgen          #+#    #+#             */
/*   Updated: 2024/02/05 12:36:05 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exec_cmd(char *cmd, char **envp)
{
	char	*path_to_cmd;
	char	**cmd_options;

	cmd_options = ft_split(cmd, ' ');
	path_to_cmd = ft_get_path(cmd_options[0], envp);
	if (execve(path_to_cmd, cmd_options, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd_options[0], 2);
		ft_free_char_tab(cmd_options);
		exit(5);
	}
}

void	ft_parent(char **argv, int *pipefd, char **envp)
{
	int		fd;
	t_flag	f_read;

	f_read = flag_read;
	fd = ft_open(argv[1], f_read);
	dup2(fd, 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	ft_exec_cmd(argv[2], envp);
}

void	ft_child(char **argv, int *pipefd, char **envp)
{
	int		fd;
	t_flag	f_write;

	f_write = flag_write;
	fd = ft_open(argv[4], f_write);
	dup2(fd, 1);
	dup2(pipefd[0], 0);
	close(pipefd[1]);
	ft_exec_cmd(argv[3], envp);
}
