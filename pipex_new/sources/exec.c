/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:42:34 by romain            #+#    #+#             */
/*   Updated: 2024/03/12 18:10:20 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_cmd_1(char *cmd, int *pipefd, int *filefd, char **envp)
{
	char	*cmd_path;
	char	**s_cmd;
	
	dup2(pipefd[1], 1); // replace stdout with pipe out
	close(pipefd[0]); // close pipe read end
	close(pipefd[1]); // close pipe write end since stdout replaced
	dup2(filefd[0], 0); // replace stdin with infile
	s_cmd = ft_split(cmd, ' ');
	cmd_path = ft_get_path(s_cmd[0], envp);
	if (execve(cmd_path, s_cmd, envp) == -1) // exec cmd
	{
		err_msg(ERR_EXEC);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_char_tab(s_cmd);
	}
}

void	exec_cmd_2(char *cmd, int *pipefd, int *filefd, char **envp)
{
	char	*cmd_path;
	char	**s_cmd;
	
	dup2(pipefd[0], 0); // replace stdin with pipe in
	close(pipefd[1]); // close pipe write end
	close(pipefd[0]); // close pipe read end since stdin replaced
	dup2(filefd[1], 1); // replace stdout with infile
	s_cmd = ft_split(cmd, ' ');
	cmd_path = ft_get_path(s_cmd[0], envp);
	if (execve(cmd_path, s_cmd, envp) == -1) // exec cmd
	{
		err_msg(ERR_EXEC);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_char_tab(s_cmd);
	}
}
