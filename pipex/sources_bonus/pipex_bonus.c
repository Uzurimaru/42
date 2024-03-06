/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:06:55 by rwintgen          #+#    #+#             */
/*   Updated: 2024/03/06 15:13:37 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd_outfile;
	int		fd_infile;
	int		arg_cursor;

	arg_cursor = 2;
	ft_basic_check(argc, argv, envp);
	if (!(ft_strcmp(argv[1], "here_doc"))) // if argv[1] == here_doc
		ft_handle_heredoc(argc, argv, &arg_cursor, &fd_outfile); // call heredoc handler function
	else
	{
		fd_infile = ft_open(argv[1], flag_read); // open infile & get fd
		fd_outfile = ft_open(argv[argc - 1], flag_write); // open outfile & get fd
		dup2(fd_infile, 0); // replace stdin with infile
		close(fd_infile); // close infile
	}
	while (arg_cursor < argc - 2) // iterate through commands except the last one
	{
		ft_create_pipe(argv[arg_cursor], envp, fd_outfile); // pipe command that is not the last one
		arg_cursor++; // go to the next one
	}
	dup2(fd_outfile, 1); // once it is the last command, replace stdout with outfile
	close(fd_outfile); // close outfile
	ft_exec_cmd(argv[arg_cursor], envp); // exec last command
	return (0);
}
