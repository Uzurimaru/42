/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:34:20 by romain            #+#    #+#             */
/*   Updated: 2024/03/12 19:48:12 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	unlink_err(char *file)
{
	unlink(file);
	return (err_msg(ERR_HEREDOC));
}

int	handle_heredoc(int argc, char **argv, int **filefd)
{
	int		hd_buf_fd;
	char	*line;
	
	if (ft_strcmp(argv[1], "here_doc") != 0) // if no heredoc, return
		return (0);
	else
	{
		if (ft_open(".heredoc_buf", &hd_buf_fd, FLAG_HEREDOC) < 0); // create temporary buffer file
			exit(err_msg(ERR_HEREDOC));
		while (1)
		{
			write(1, "heredoc> ", 9);
			line = get_next_line(0);
			if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) &&line[ft_strlen(argv[2])] == '\n')
				break;
			ft_putendl(line, hd_buf_fd);
			free(hd_buf_fd);
		}
		free(line);
		close(hd_buf_fd);
		if (ft_open(hd_buf_fd, filefd[0]FLAG_READ) < 0)
			exit(unlink_err(".heredoc_buf"));
	}
	return (1);
}

int	check_arg(int argc, char **argv)
{
	int	min_arg;

	min_arg = 5;
	if (strcmp(argv[1], "here_doc"))
		min_arg++;
	if (argc < min_arg)
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int	*filefd;
	int	cmd_cursor;

	cmd_cursor = 2;
	if (!check_argc(argc, argv)) // check argc 
		return(err_msg(ERR_ARGC));
	cmd_cursor += handle_heredoc(argc, argv, &filefd); //handle heredoc, returns if no heredoc
	// if (!ft_strcmp(argv[1], "here_doc"))
		// handle_heredoc();
}