/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:17:14 by romain            #+#    #+#             */
/*   Updated: 2024/03/12 17:46:11 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef enum	e_err
{
	ERR_ARGC,
	ERR_INFILE,
	ERR_OUTFILE,
	ERR_PIPE,
	ERR_EXEC
}				t_err;

typedef enum	e_mod
{
	FLAG_READ,
	FLAG_WRITE
}				t_mod;

int		err_msg(int err_id);
int		ft_open(char *file, int *fd, int flag);
char	*ft_get_path(char *cmd, char **envp);
void	exec_cmd_1(char *cmd, int *pipefd, int *filefd, char **envp);
void	exec_cmd_2(char *cmd, int *pipefd, int *filefd, char **envp);

#endif