/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:38:33 by rwintgen          #+#    #+#             */
/*   Updated: 2024/03/04 10:05:06 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	ft_open(char *file, t_flag flag)
{
	int	fd;

	if (flag == flag_read)
		fd = open(file, O_RDONLY, 0777);
	else if (flag == flag_write)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flag == flag_heredoc)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
		exit(4);
	return (fd);
}

char	*ft_find_env_path(char **envp)
{
	int		i;
	int		j;
	char	*envp_name;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=' && envp[i][j])
			j++;
		envp_name = ft_substr(envp[i], 0, j);
		if (!(ft_strcmp(envp_name, "PATH")))
		{
			free(envp_name);
			return (envp[i] + j + 1);
		}
		free(envp_name);
		i++;
	}
	return (NULL);
}

char	*ft_get_path(char *cmd, char **envp)
{
	char	**cmd_elements;
	char	**sep_env_paths;
	char	*tmp;
	char	*cmd_full_path;
	int		i;

	sep_env_paths = ft_split(ft_find_env_path(envp), ':');
	cmd_elements = ft_split(cmd, ' ');
	i = -1;
	while (sep_env_paths[++i])
	{
		tmp = ft_strjoin(sep_env_paths[i], "/");
		cmd_full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_full_path, F_OK | X_OK) == 0)
		{
			ft_free_char_tab(sep_env_paths);
			ft_free_char_tab(cmd_elements);
			return (cmd_full_path);
		}
		free(cmd_full_path);
	}
	ft_free_char_tab(sep_env_paths);
	ft_free_char_tab(cmd_elements);
	return (cmd);
}

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

void	ft_create_pipe(char *cmd, char **envp, int fd_outfile)
{
	int	pipefd[2];
	int	pipe_ret;
	int	pid;

	pipe_ret = pipe(pipefd);
	if (pipe_ret < 0)
		exit(9);
	pid = fork();
	if (pid < 0)
		exit(10);
	else if (pid == 0)
	{
		close(fd_outfile);
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
