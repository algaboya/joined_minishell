/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:21:20 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/01 17:25:03 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_cmd_lst(t_cmd_lst *cmd_lst)
// {
// 	t_cmd_lst	*temp;
// 	int			i;

// 	i = 0;
// 	temp = NULL;
// 	while (cmd_lst)
// 	{
// 		temp = cmd_lst;
// 		free(temp->cmd);
// 		if (temp->args)
// 		{
// 			while (temp->args[i])
// 			{
// 				free(temp->args[i]);
// 				i++;
// 			}
// 			free(temp->args);
// 		}
// 		free(temp);
// 		cmd_lst = cmd_lst->next;
// 	}
//     free(cmd_lst);
//     cmd_lst = NULL;
// }

// void	free_cmd_lst(t_cmd_lst **cmd_lst)
// {
// 	// t_cmd_lst	*temp;
// 	// int			i;

// 	// if (!cmd_lst || !*cmd_lst)
// 	// 	return;
// 	// while (*cmd_lst)
// 	// {
// 	// 	temp = *cmd_lst;
// 	// 	i = 0;
// 	// 	// free(temp->cmd);
// 	// 	free_set_null(temp->cmd);
// 	// 	if (temp->args)
// 	// 	{
// 	// 		while (temp->args[i])
// 	// 		{
// 	// 			free_set_null(temp->args[i]);
// 	// 			i++;
// 	// 		}
// 	// 		free(temp->args);
// 	// 		temp->args = NULL;
// 	// 	}
// 	// 	free(temp);
// 	// 	temp = NULL;
// 	// 	// if (  (*cmd_lst))
// 	// 		*cmd_lst = (*cmd_lst)->next;
// 	// }
// 	// *cmd_lst = NULL;
// }


#include <stdlib.h>

void free_cmd_lst(t_cmd_lst *tmp_cmd_lst)
{
    int i = 0;
    t_cmd_lst *tmp;

    while (tmp_cmd_lst)
    {
        tmp = tmp_cmd_lst->next; 
        free(tmp_cmd_lst->cmd);

        if (tmp_cmd_lst->args)
        {
			i =  0;
            while (tmp_cmd_lst->args[i])
            {
				free_set_null(tmp_cmd_lst->args[i]);
                i++;
            }
			free_set_null(tmp_cmd_lst->args[i]);
			free(tmp_cmd_lst->args);
			tmp_cmd_lst->args = NULL;
			// free_set_null(tmp_cmd_lst->args);
        }

        free(tmp_cmd_lst->heredoc);
        free(tmp_cmd_lst->red_in);
        free(tmp_cmd_lst->red_out);
        free(tmp_cmd_lst->red_append);

        free(tmp_cmd_lst); // Free the current node
        tmp_cmd_lst = tmp; // Move to the next node
    }
}



void    free_tok_lst(t_token *tok_lst)
{
    t_token *tmp;

    while (tok_lst)
    {
        tmp = tok_lst;
        if (tmp->context)
        {
            free(tmp->context);
            tmp->context = NULL;
        }
        free(tmp);
		tok_lst = tok_lst->next;
        write(1, "FREE TOK\n", 9);
    }
    free(tok_lst);
    tok_lst = NULL;
}

void	free_env_lst(t_env *env_lst)
{
	t_env	*temp;

	while (env_lst)
	{
		temp = env_lst->next;
		if (env_lst->key)
		{
			free(env_lst->key);
			env_lst->key = NULL;
		}
		if (env_lst->value)
		{
			free(env_lst->value);
			env_lst->value = NULL;
		}
		free(env_lst);
		env_lst = temp;
	}
	free(env_lst);
	env_lst = NULL;
}

void	free_doll_lst(t_dollar *doll_lst)
{
	t_dollar	*tmp;

	tmp = doll_lst;
	while (doll_lst)
	{
		tmp = doll_lst->next;
		free(doll_lst->u_key);
		doll_lst->u_key = NULL;
		free(doll_lst->value);
		doll_lst->value = NULL;
		free(doll_lst);
		doll_lst = tmp;
	}
	free(doll_lst);
	doll_lst = NULL;
}

void	free_set_null(char *tmp)
{
	free(tmp);
	tmp = NULL;
}
