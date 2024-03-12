/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:34:47 by romain            #+#    #+#             */
/*   Updated: 2024/03/12 19:29:21 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	ERR_EXEC,
	ERR_HEREDOC
}				t_err;

typedef enum	e_mod
{
	FLAG_READ,
	FLAG_WRITE,
	FLAG_HEREDOC
}				t_mod;

int		err_msg(int err_id);
int		ft_open(char *file, int *fd, int flag);
char	*ft_get_path(char *cmd, char **envp);

#endif
