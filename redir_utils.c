/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:19:48 by algaboya          #+#    #+#             */
/*   Updated: 2025/01/27 18:18:49 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redir_out(t_shell *general, char *name, int append)
{
	int	fd;

	if (general->curr_cmd->std_out == -1 || general->curr_cmd->std_in == -1)
		return (-1);
	if (append)
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}
int	open_infile(t_shell *general, char *name)
{
	int	fd;

	if (general->curr_cmd->std_out == -1 || general->curr_cmd->std_in == -1)
		return (-1);
	fd = open(name, O_RDONLY);
	return (fd);
}

void	in_redir(t_cmd_lst *lst)
{
	if (lst->std_in > 0)
	{
		if (dup2(lst->std_in, 0) < 0)
		{
			ft_putstr_fd("minishell: Dup Error\n", 2);
			set_exit_status(EXIT_FAILURE);
		}
		close(lst->std_in);
	}
}

void	out_redir(t_cmd_lst *lst)
{
	if (lst->std_out > 0)
	{
		if (dup2(lst->std_out, 1) < 0)
		{
			ft_putstr_fd("minishell: Dup Error\n", 2);
			set_exit_status(EXIT_FAILURE);
		}
		close(lst->std_out);
	}
}

void	redir_dups(t_cmd_lst *lst)
{
	in_redir(lst);
	out_redir(lst);
}