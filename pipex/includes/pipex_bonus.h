/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:32:26 by rwintgen          #+#    #+#             */
/*   Updated: 2024/02/10 10:42:53 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef enum e_flag
{
	flag_read,
	flag_write,
	flag_heredoc
}	t_flag;

void	ft_exec_cmd(char *cmd, char **envp);
void	ft_parent(char **argv, int *pipefd, char **envp);
void	ft_child(char **argv, int *pipefd, char **envp);

int		ft_open(char *file, t_flag flag);
char	*ft_find_env_path(char **envp);
char	*ft_get_path(char *cmd, char **envp);

void	ft_read_heredoc(char **argv);

#endif