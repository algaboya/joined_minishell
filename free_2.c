/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 02:09:11 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/04 17:42:58 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fd(t_shell *general)
{
	if (general->pipe_count > 0)
	{
		free(general->fd);
		general->fd = NULL;
	}
}

void	free_set_null(void *tmp)
{
	free(tmp);
	tmp = NULL;
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	cmd_free(t_shell *general)
{
	if (general->cmd_lst)
	{
		free_cmd_lst(general->cmd_lst);
		general->cmd_lst = NULL;
	}
	else
		return ;
}

void	ft_kill_proc(t_cmd_lst *start, t_cmd_lst *end)
{
	if (start != end)
		ft_kill_proc(start->next, end);
	if (start->pid > 0)
		kill(start->pid, SIGKILL);
	waitpid(start->pid, NULL, 0);
	start->pid = -1;
}
