/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:55:03 by algaboya          #+#    #+#             */
/*   Updated: 2025/01/27 01:27:32 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_builtin(t_shell *general)  //need argssssss
{
	int i;
    int j;
    int line_flag;

    i = 1;
    j = 2;
    line_flag = 0;
    if (!general->cmd_lst->args[i])
        return (ft_putstr_fd("\n", 1), 0);
    if (ft_strcmp(general->cmd_lst->args[i], "-n") == 0)
    {
        while (general->cmd_lst->args[i][j] == 'n')
            j++;
        line_flag = 1;
    }
    while (general->cmd_lst->args && general->cmd_lst->args[i])
    {
        ft_putstr_fd(general->cmd_lst->args[i], 1);
        i++;
        if (general->cmd_lst->args[i])
            ft_putstr_fd(" ", 1);
    }
    if (line_flag == 0)
    {    ft_putstr_fd("\n", 1);}
    set_exit_status(SUCCESS_EXIT);
	return (SUCCESS_EXIT);
}

