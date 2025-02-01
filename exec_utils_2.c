/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:07:27 by tumolabs          #+#    #+#             */
/*   Updated: 2025/02/01 17:50:56 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ************************
// *** CAUTION *** FULL ***
// ************************

void    close_exit(t_shell *general)
{
    write(2, "Dup Error\n", 10);
    close_pipes(general->fd, general->pipe_count);
    clean_gen_exit(general, 1, 0, 1);
}

int is_abs_rel_path(char *cmd)
{
    if (cmd[0] == '.' || (cmd[0] == '.' && cmd[1] == '/') || (cmd[0] == '.' && cmd[1] == '.'
        && cmd[2] == '/') || cmd[0] == '/' || cmd[0] == '~')
        return (1);
    return (0);
}

void    mini_error(char *error, int fd)
{
    ft_putstr_fd("minisHell: ", fd);
    ft_putstr_fd(error, fd);
    ft_putstr_fd(": command not found\n", fd);
}

char *the_path(char **splitted, char *cmd)
{
    char    *joined;
    char    **tmp = splitted;
    char    *temp;

    while (*tmp)
    {
        temp = ft_strjoin(*tmp, "/");
        joined = ft_strjoin(temp, cmd);
        free_set_null(temp);
        // printf("_______joined = %s\n", joined);
        if (access(joined, F_OK) == 0)
        {
            // write(1, "abuba\n", 6);
            return (joined);
        }
        free(joined);
        tmp++;
    }
    return (NULL);
}

void    clean_gen_exit(t_shell *general, int number, int cmd, int exitik)
{
	set_exit_status(number);
    if (cmd == 1)
    {
        free_cmd_lst(general->cmd_lst);
        general->cmd_lst = NULL;
    }
	free(general->doll_lst);
    general->doll_lst = NULL;
    free_env_lst(general->env_lst);
    free_env_lst(general->sorted_env_lst);
	close(general->original_stdin);
	close(general->original_stdout);
    if (general->pipe_count > 0)
    {  
        free(general->fd);
        general->fd = NULL;
    }
    // general->cmd_lst = NULL;
    general->env_lst = NULL;
    general->sorted_env_lst = NULL;
    free(general);
    if (exitik == 1)
        exit(number);
}
