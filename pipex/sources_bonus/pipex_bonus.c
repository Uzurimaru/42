/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:34:20 by romain            #+#    #+#             */
/*   Updated: 2024/03/20 15:04:02 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int	filefd[2];
	int	arg_cursor;

	arg_cursor = 1;
	if (!check_argc(argc, argv))
		return (err_msg(ERR_ARGC));
	arg_cursor += handle_heredoc(argv, filefd);
	set_inf_outf_fds(filefd, argc, argv, arg_cursor);
	dup2(filefd[0], 0);
	close(filefd[0]);
	while (++arg_cursor < argc - 2)
		exec_piped_commands(argv[arg_cursor], envp, filefd, argv);
	if (!ft_strcmp(argv[1], "here_doc"))
		unlink(".heredoc_buf");
	ft_exec_last(argv[arg_cursor], envp, filefd);
	// wait all
	ft_wait_all();
	return (0);
}
