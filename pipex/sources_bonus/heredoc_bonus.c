/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:33:25 by romain            #+#    #+#             */
/*   Updated: 2024/03/18 10:46:35 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	unlink_err(char *file)
{
	unlink(file);
	return (err_msg(ERR_HEREDOC));
}

int	handle_heredoc(char **argv, int *filefd)
{
	int		hd_buf_fd;
	char	*line;

	if (ft_strcmp(argv[1], "here_doc") != 0)
		return (0);
	else
	{
		if (ft_open(".heredoc_buf", &hd_buf_fd, FLAG_HEREDOC) < 0)
			exit(err_msg(ERR_HEREDOC));
		while (1)
		{
			write(1, "heredoc> ", 9);
			line = get_next_line(0);
			if (!ft_strncmp(line, argv[2], ft_strlen(argv[2])) && \
				line[ft_strlen(argv[2])] == '\n')
				break ;
			ft_putstr_fd(line, hd_buf_fd);
			free(line);
		}
		free(line);
		close(hd_buf_fd);
		if (ft_open(".heredoc_buf", filefd, FLAG_READ) < 0)
			exit(unlink_err(".heredoc_buf"));
	}
	return (1);
}
