/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:34:20 by romain            #+#    #+#             */
/*   Updated: 2024/03/13 18:12:10 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// TODO .heredoc_buf does not delete

int	main(int argc, char **argv, char **envp)
{
	int	*filefd;
	int	arg_cursor;

	arg_cursor = 1;
	if (!check_argc(argc, argv)) // check argc 
		return (err_msg(ERR_ARGC));
	arg_cursor += handle_heredoc(argv, &filefd); //handle heredoc, returns 0 if no heredoc
	set_inf_outf_fds(&filefd, argc, argv, arg_cursor);
	dup2(filefd[0], 0); // redirect input 
	close(filefd[0]);
	while (++arg_cursor < argc - 2)
		exec_piped_commands(argv[arg_cursor], envp, filefd); // exec piped commands
	if (!ft_strcmp(argv[1], "here_doc"))
		unlink(".heredoc_buf");
	ft_exec_last(argv[arg_cursor], envp, filefd); // exec last cmd after redirecting output
	return (0);
}