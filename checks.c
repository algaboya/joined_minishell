/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:18:10 by elen_t13          #+#    #+#             */
/*   Updated: 2025/02/04 17:45:08 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sgmnt_cpy(char *input, int *i)
{
	int		j;
	int		length;
	char	*result;

	length = 0;
	if (input[*i] == '?')
		length++;
	else
	{
		while (input[*i + length] && input[*i + length] != ' '
			&& input[*i + length] != '"' && input[*i + length] != '$'
			&& input[*i + length] != '\'')
			length++;
	}
	result = (char *)malloc((length + 1) * sizeof(char));
	j = 0;
	while (input[*i] && input[*i] != ' ' && input[*i] != '$'
		&& input[*i] != '\"' && input[*i] != '\'' && j < length)
	{
		result[j++] = input[*i];
		(*i)++;
	}
	result[j] = '\0';
	return (result);
}

char	*open_dollar(t_shell *general, char *input, int *i)
{
	if (input[*i] && input[*i] == '$')
	{		
		(*i)++;
		if (input[*i] == '?' && input[*i + 1])
			general->doll_lst->value = ft_itoa(get_exit_status());
		general->doll_lst->u_key = sgmnt_cpy(input, i);
		if (!general->doll_lst->u_key[0])
		{	
			general->doll_lst->value = (char *)malloc(sizeof(char) * 2);
			check_malloc(general, general->doll_lst->value);
			general->doll_lst->value[0] = '$'; 
			general->doll_lst->value[1] = '\0'; 
		}
		else
			general->doll_lst->value = check_env_var(general->env_lst, general->doll_lst->u_key);
		if (!general->doll_lst->value)
		{	
			general->doll_lst->value = (char *)malloc(sizeof(char) * 1);
			check_malloc(general, general->doll_lst->value);
			general->doll_lst->value[0] = '\0'; 
		}
	}
	return (general->doll_lst->value);
}

int	check_inp_quotes(t_shell *general, char *input, int i, int start)
{
	int	flag_sg;
	int	flag_db;

	flag_sg = 0;
	flag_db = 0;
	i = start;
	(void)general;
	while (input[i])
	{
		if (input[i] == '\"' && !flag_sg)
			flag_db = !flag_db;
		else if (input[i] == '\'' && !flag_db)
			flag_sg = !flag_sg;
		i++;
	}
	if (flag_db || flag_sg)
		return (printf("Error: Unclosed quotes found in input.\n"), -1);
	return (0);
}
