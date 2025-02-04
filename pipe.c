/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:15:45 by tumolabs          #+#    #+#             */
/*   Updated: 2025/02/04 17:44:31 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe(t_shell *general)
{
	int	i;
	int	(*fd)[2];

	i = 0;
	fd = malloc(sizeof (int [2]) * general->pipe_count);
	if (!fd)
		malloc_exit(general);
	while (i < general->pipe_count)
	{
		if (pipe(fd[i++]) == -1)
		{
			while (i > 0)
			{
				if (fd[i][0])
					close(fd[i][0]);
				if (fd[i][1])
					close(fd[i][1]);
				--i;
			}
			general->pipe_count = -1;
			return (free(fd), -1);
		}
	}
	general->fd = fd;
	return (EXIT_SUCCESS);
}

void	close_pipes(int (*fd)[2], int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (fd[i][0])
			close(fd[i][0]);
		if (fd[i][1])
			close(fd[i][1]);
		i++;
	}
}

int	pipe_fork(t_shell *general, t_cmd_lst *tmp_cmd_lst, int index)
{
	int	i;

	i = 0;
	create_pipe(general);
	if (general->pipe_count < 0)
	{
		ft_putstr_fd("MinisHell: fork: Resource temporarily unavailable\n", 2);
		return (-1);
	}
	while (i < (general->pipe_count + 1))
	{
		execute(general, tmp_cmd_lst, index);
		if (tmp_cmd_lst->pid < 0)
		{
			ft_kill_proc(general->cmd_lst, tmp_cmd_lst);
			ft_putstr_fd("MinisHell: fork:", 2);
			ft_putstr_fd("Resource temporarily unavailable\n", 2);
			return (-1);
		}
		index++;
		tmp_cmd_lst = tmp_cmd_lst->next;
		i++;
	}
	close_pipes(general->fd, general->pipe_count);
	return (index);
}

void	waiting(pid_t pid, int *_status)
{
	waitpid(pid, _status, 0);
	if (WIFSIGNALED(*_status))
	{
		*_status = WTERMSIG(*_status) + 128;
		if (*_status == 131)
			write(1, "Quit: 3\n", 9);
		return (set_exit_status(*_status));
	}
	set_exit_status(WEXITSTATUS(*_status));
}

int	pipe_count(t_token *tok_lst)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = tok_lst;
	while (tmp)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
