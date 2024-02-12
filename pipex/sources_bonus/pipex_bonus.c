/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:06:55 by rwintgen          #+#    #+#             */
/*   Updated: 2024/02/12 16:03:00 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// TODO missing 1 free on heredocs
// TODO too many FDs open at end of program

// clear && valgrind --leak-check=full --track-origins=yes --track-fds=yes --trace-children=yes ./pipex_bonus infile "cat" "grep TEST" "wc -l" outfile

int	main(int argc, char **argv, char **envp)
{
	int		fd_outfile;
	int		fd_infile;
	int		arg_cursor;

	arg_cursor = 2;
	if (argc < 5)
	{
		ft_putstr_fd("./pipex_bonus infile cmds outfile\n", 2);
		exit(1);
	}
	if (!(ft_strcmp(argv[1], "here_doc")))
	{
		arg_cursor++;
		if (argc < 6)
		{
			ft_putstr_fd("./pipex_bonus here_doc limiter cmds file\n", 2);
			exit(1);
		}
		fd_outfile = ft_open(argv[argc - 1], (t_flag)2);
		ft_read_heredoc(argv);
	}
	else
	{
		fd_infile = ft_open(argv[1], (t_flag)0);
		fd_outfile = ft_open(argv[argc - 1], (t_flag)1);
		dup2(fd_infile, 0);
	}
	while (arg_cursor < argc - 2)
	{
		ft_create_pipe(argv[arg_cursor], envp);
		arg_cursor++;
	}
	dup2(fd_outfile, 1);
	ft_exec_cmd(argv[arg_cursor], envp);
	return (0);
}
