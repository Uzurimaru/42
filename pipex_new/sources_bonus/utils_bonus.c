/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:20:13 by romain            #+#    #+#             */
/*   Updated: 2024/03/12 19:27:23 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	err_msg(int err_id)
{
	if (err_id == ERR_ARGC)
		ft_putstr_fd("pipex: need 4 arguments\n", 2);
	if (err_id == ERR_INFILE)
		ft_putstr_fd("pipex: can't access infil\ne", 2);
	if (err_id == ERR_OUTFILE)
		ft_putstr_fd("pipex: can't access outfile\n", 2);
	if (err_id == ERR_PIPE)
		ft_putstr_fd("pipex: pipe failed\n", 2);
	if (err_id == ERR_EXEC)
		ft_putstr_fd("pipex: command not found:\n", 2);
	if (err_id == ERR_HEREDOC)
		ft_putstr_fd("pipex: heredoc error\n");
	return (err_id);
}

int	ft_open(char *file, int *fd, int flag)
{
	if (flag == FLAG_READ)
		*fd = open(file, O_RDONLY);
	else if (flag == FLAG_WRITE)
		*fd = open(file, O_TRUNC | O_CREAT | O_RDWR, 0644);
	else if (flag == FLAG_HEREDOC)
		*fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (*fd);
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
	char	**sep_env_paths;
	char	*tmp;
	char	*cmd_full_path;
	int		i;

	sep_env_paths = ft_split(ft_find_env_path(envp), ':');
	i = 0;
	while (sep_env_paths[i]) 
	{
		tmp = ft_strjoin(sep_env_paths[i], "/");
		cmd_full_path = ft_strjoin(tmp, cmd); // add the command
		free(tmp);
		if (access(cmd_full_path, F_OK | X_OK) == 0)
		{
			ft_free_char_tab(sep_env_paths);
			return (cmd_full_path);
		}
		free(cmd_full_path);
		i++;
	}
	ft_free_char_tab(sep_env_paths);
	return(cmd);
}
