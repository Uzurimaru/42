/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:34:20 by romain            #+#    #+#             */
/*   Updated: 2024/03/14 13:20:26 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// TODO .heredoc_buf does not delete

int	main(int argc, char **argv, char **envp)
{
	int	filefd[2]; // manage this
	int	arg_cursor;

	arg_cursor = 1;
	if (!check_argc(argc, argv)) // check argc
		return (err_msg(ERR_ARGC));
	arg_cursor += handle_heredoc(argv, filefd); //handle heredoc, returns 0 if no heredoc
	set_inf_outf_fds(filefd, argc, argv, arg_cursor);
	// TODO fd_putstr inf
	dup2(filefd[0], 0); // redirect input
	close(filefd[0]);
	while (++arg_cursor < argc - 2)
		exec_piped_commands(argv[arg_cursor], envp, filefd); // exec piped commands
	if (!ft_strcmp(argv[1], "here_doc"))
		unlink(".heredoc_buf");
	ft_exec_last(argv[arg_cursor], envp, filefd); // exec last cmd after redirecting output
	return (0);
}
