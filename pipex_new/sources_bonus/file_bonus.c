/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:10:58 by romain            #+#    #+#             */
/*   Updated: 2024/03/13 18:05:36 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	ft_open(char *file, int *fd, int flag)
{
	if (flag == FLAG_READ)
		*fd = open(file, O_RDONLY);
	else if (flag == FLAG_WRITE)
		*fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (flag == FLAG_HEREDOC)
		*fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (*fd);
}

void set_inf_outf_fds(int **filefd, int argc, char **argv, int arg_cursor)
{
	int	fd_inf;
	int	fd_outf;
	
    if (arg_cursor == 1) // open infile if no heredoc
		fd_inf = ft_open(argv[arg_cursor], &(*filefd)[0], FLAG_READ);
	else // keep as is
		fd_inf = (*filefd)[0];
    if (arg_cursor == 1) // open outfile with flag write if no heredoc
		fd_outf = ft_open(argv[argc - 1], &(*filefd)[1], FLAG_WRITE);
	else // else open outfile with flag heredoc
		fd_outf = ft_open(argv[argc - 1], &(*filefd)[1], FLAG_HEREDOC);
    if (fd_inf < 0)
		exit(err_msg(ERR_INFILE));
	if (fd_outf < 0)
		exit(err_msg(ERR_OUTFILE));
}
