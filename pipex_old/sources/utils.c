/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:38:33 by rwintgen          #+#    #+#             */
/*   Updated: 2024/03/10 14:03:11 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_open(char *file, t_flag flag)
{
	int	fd;

	fd = -1;
	if (flag == flag_read) // open in RD for reading from infile
		fd = open(file, O_RDONLY, 0777);
	else if (flag == flag_write)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777); // open with RDWR and TRUNC to reset output in outfile
	if (fd < 0) // if open fails
		exit(4);
	return (fd);
}

char	*ft_find_env_path(char **envp)
{
	int		i;
	int		j;
	char	*envp_name;

	i = 0;
	while (envp[i]) // iterate through enironment variables
	{
		j = 0;
		while (envp[i][j] != '=' && envp[i][j]) // iterate until '='
			j++;
		envp_name = ft_substr(envp[i], 0, j); // grab environment variable name up to '='
		if (!(ft_strcmp(envp_name, "PATH"))) // if it is PATH
		{
			free(envp_name);
			return (envp[i] + j + 1); // return everything after the '='
		}
		free(envp_name); // else try the next environment variable
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

	sep_env_paths = ft_split(ft_find_env_path(envp), ':'); // fetch the $PATH sppecified paths and split them
	i = -1;
	while (sep_env_paths[++i]) // iterate through all the paths 
	{
		tmp = ft_strjoin(sep_env_paths[i], "/"); // add a '/' at the end
		cmd_full_path = ft_strjoin(tmp, cmd); // add the command
		free(tmp);
		if (access(cmd_full_path, F_OK | X_OK) == 0) // if command is found after path
		{
			ft_free_char_tab(sep_env_paths); // free stuff
			return (cmd_full_path); // return the valid path and command combination
		}
		free(cmd_full_path); // else free and try next one
	}
	ft_free_char_tab(sep_env_paths); // if command not found, free and return command for error mgmt
	return (cmd);
}
