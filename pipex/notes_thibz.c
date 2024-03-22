

int	close_if_not_std(int fd) {
	if (fd != STDIN_FILENO && fd != STDOUT_FILENO) {
		return close(fd);
	}
	return (0);
}

int ft_exec_commands(int num_command,  const char *commands[], int infile_fd, int outfile_fd, const char *envp[]) {

	int i;
	int fds[2];
	int fd_in;
	int fd_out;
	
	i = 0;
	fd_in = infile_fd;
	while (i < num_command) {
		if (i < num_command - 1) {
			pipe(fds);
			fd_out = fds[1];
		} else {
			fd_out = outfile_fd;
		}
		ft_exec_command(commands[i], envp, fd_in, fd_out);
		close_if_not_std(fd_out);
		close_if_not_std(fd_in);
		fd_in = fds[0];
	}
}

int ft_exec_command(const char *cmd, const char *envp[], int fd_in, int fd_out)
{
	int pid;

	pid = fork();
	if (pid < 0) {
		return pid;
	}
	if (pid == 0) {
		return pid;
	}
	dup2(fd_in, STDIN_FILENO);
	close_if_not_std(fd_in);
	dup2(fd_out, STDOUT_FILENO);
	close_if_not_std(fd_out);
	char	**argv = ft_split(cmd, ' ');
	char const command_name = ft_find_command(argv[0], envp);
	execve(command_name, argv, envp);
	exit(-1);
	return (-1);
}