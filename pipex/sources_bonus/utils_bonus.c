/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:38:33 by rwintgen          #+#    #+#             */
/*   Updated: 2024/02/10 13:13:01 by rwintgen         ###   ########.fr       */
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
	char	*all_env_paths;
	char	*cmd_full_path;
	int		i;

	all_env_paths = ft_find_env_path(envp);
	envp = ft_split(all_env_paths, ':');
	cmd_elements = ft_split(cmd, ' ');
	i = 0;
	while (envp[i])
	{
		envp[i] = ft_strjoin(envp[i], "/");
		cmd_full_path = ft_strjoin(envp[i], cmd);
		if (access(cmd_full_path, F_OK | X_OK) == 0)
		{
			// ft_free_char_tab(envp);
			ft_free_char_tab(cmd_elements);
			return (cmd_full_path);
		}
		i++;
	}
	ft_free_char_tab(envp);
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

void	ft_write_heredoc(char **argv, int *pipefd)
{
	char	*line;
	int		sep_len;

	close(pipefd[0]);
	sep_len = ft_strlen(argv[2]);
	ft_strjoin(argv[2], "\n");
	while (1)
	{
		ft_printf("heredoc> ");
		line = get_next_line(0);
		if (line == NULL)
			strdup();
		if (ft_strncmp(line, argv[2], sep_len) == 0)
		{
			free(line);
			exit(8);
		}
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
}

void	ft_read_heredoc(char **argv)
{
	int		pipefd[2];
	int		pipe_ret;
	pid_t	pid;

	pipe_ret = pipe(pipefd);
	if (pipe_ret < 0)
		exit(6);
	pid = fork();
	if (pid < 0)
		exit(7);
	if (pid == 0)
		ft_write_heredoc(argv, pipefd);
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		wait(NULL);
	}
}

void	ft_create_pipe(char *cmd, char **envp)
{
	// TODO faire la fonction duh
}
