/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childfunctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:31:42 by invader           #+#    #+#             */
/*   Updated: 2025/12/20 16:34:32 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	sendtochild(char *limiter, int write_fd)
{
	char	*line;
	int		len;

	len = ft_strlen(limiter);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, len) && line[len] == '\n')
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		free(line);
	}
}

int	firstchildreadstin(char	*shell, char **cmd_args, char *limiter)
{
	int		pipesparent[2];
	int		pipeschild[2];
	pid_t	pid;

	if (pipe(pipesparent) == -1)
		cleanup_exit(shell, "could not create parent pipe", 1);
	if (pipe(pipeschild) == -1)
		closeandexit(pipesparent, shell, "could not create child pipes", 1);
	pid = fork();
	if (pid == -1)
	{
		cleanup_exit(shell, "fork failed", 1);
		close2(pipesparent[0], pipesparent[1]);
		close2(pipeschild[0], pipeschild[1]);
	}
	if (pid == 0)
	{
		close2(pipesparent[1], pipeschild[0]);
		child_exec(shell, cmd_args, pipesparent[0], pipeschild[1]);
	}
	close2(pipesparent[0], pipeschild[1]);
	sendtochild(limiter, pipesparent[1]);
	close(pipesparent[1]);
	return (pipeschild[0]);
}

void	cleanup_exit(t_memory *memory, const char *msg, int code)
{
	if (msg)
		perror(msg);
	free3d(memory->args);
	free2d(memory->commands);
	exit(code);
}

void	child_exec(t_memory *memory, char **cmd_args, int fd_in, int fd_out)
{
	if (fd_in != -1)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != -1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (!cmd_args || !cmd_args[0])
		cleanup_exit(memory, "no commands", 127);
	execve(cmd_args[0], cmd_args, memory->envp);
	cleanup_exit(memory, "command failed to execute", 127);
}

int	wait_for_children(pid_t last_pid)
{
	pid_t	pid;
	int		status;
	int		exit_status;
	int		found_last;

	exit_status = 0;
	found_last = 0;
	while (1)
	{
		pid = wait(&status);
		if (pid == -1)
			break ;
		if (pid == last_pid)
		{
			found_last = 1;
			if ((status & 0x7f) == 0)
				exit_status = (status >> 8) & 0xff;
			else
				exit_status = 128 + (status & 0x7f);
		}
	}
	if (!found_last)
		return (1);
	return (exit_status);
}
