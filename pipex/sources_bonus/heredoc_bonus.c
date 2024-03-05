/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:16:15 by rwintgen          #+#    #+#             */
/*   Updated: 2024/03/04 10:05:03 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_write_heredoc(char **argv, int *pipefd)
{
	char	*line;
	int		sep_len;

	close(pipefd[0]);
	sep_len = ft_strlen(argv[2]);
	while (1)
	{
		ft_printf("heredoc> ");
		line = get_next_line(0);
		if (!(ft_strncmp(line, argv[2], sep_len)) && line[sep_len] == '\n')
		{
			free(line);
			close(pipefd[1]);
			exit(8);
		}
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
}

void	ft_read_heredoc(char **argv, int fd_outfile)
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
	{
		close(fd_outfile);
		ft_write_heredoc(argv, pipefd);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		wait(NULL);
	}
}

void	ft_handle_heredoc(int argc, char **argv, int *arg_cursor, int *fd_out)
{
	*arg_cursor += 1;
	if (argc < 6)
		ft_error_msg(2);
	*fd_out = ft_open(argv[argc - 1], (t_flag)2);
	ft_read_heredoc(argv, *fd_out);
}
