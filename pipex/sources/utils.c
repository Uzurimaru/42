/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:38:33 by rwintgen          #+#    #+#             */
/*   Updated: 2024/03/05 13:08:18 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_open(char *file, t_flag flag)
{
	int	fd;

	if (flag == flag_read)
		fd = open(file, O_RDONLY, 0777);
	else if (flag == flag_write)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
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
