/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deymons <deymons@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:34:20 by romain            #+#    #+#             */
/*   Updated: 2024/03/25 16:29:00 by deymons          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// TODO Makefile "" "" outfile -> FDs open
// TODO Makefile cat cat outfile -> FDs open

void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->filefd[0] = -1;
	data->filefd[1] = -1;
	data->pipefd[0] = -1;
	data->pipefd[1] = -1;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		arg_cursor;

	init_data(&data, argc, argv, envp);
	arg_cursor = 1;
	if (!check_argc(argc, argv))
		return (err_msg(ERR_ARGC));
	arg_cursor += handle_heredoc(argv, data.filefd);
	set_inf_outf_fds(data.filefd, argc, argv, arg_cursor);
	exec_piped_commands(arg_cursor, data);
	if (!ft_strcmp(argv[1], "here_doc"))
		unlink(".heredoc_buf");
	ft_wait_all();
	return (0);
}
