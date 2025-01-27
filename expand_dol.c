/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:13:47 by elen_t13          #+#    #+#             */
/*   Updated: 2025/01/27 04:13:35 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// *********************
// ****CAUTION FULL*****
// *********************
// 4 function

void	expand_var(char **input, t_shell *general, int *start, int *i)
{
	int len;
	len = 0;
	*input = countcpy_len(*input, *start, &len, general);
	*start = 0;
	*i = len;
	return ;
}
int spec_len(char *input, int start)
{
	int i;

	i = 0;
	while (input[start])
	{
		start++;
		i++;
	}
	return (i);
}
char *countcpy_len(char *input, int start, int *l, t_shell *general)
{
	int i;
	char *copy;
	int len;
	int val_len;

	len = 0;
	i = start;
	while (input[start] && input[start] != '$')
	{
		start++;
		len++;
	}
	*l = len + ft_strlen(general->doll_lst->u_key);
	val_len = ft_strlen(general->doll_lst->value);	
	copy = (char *)malloc(sizeof(char) * (val_len + len + spec_len(input, *l) + 1));
	check_malloc(copy);
	ft_strcpy(copy, input, i, len);
	ft_strcpy_2(copy, general->doll_lst->value, len, val_len);
	ft_strcpy_3(copy, input, (val_len + len), (*l + i + 1));
	*l = val_len + len;

	return (copy);
} // echo ba"rev $USER jan" vonc es

// char	*only_for_dol_harcakan(t_shell *general)
// {
//     char *status_str;

//     status_str = ft_itoa(get_exit_status());
//     general->doll_lst->u_key = ft_strdup("?");
//     general->doll_lst->value = status_str;
//     return (status_str);
// }

int	check_cut_quotes(t_shell *general, char **input, int *i, int start)
{
	if (check_inp_quotes(general, *input, *i, start) == -1)
		return (-1);
	while ((*input)[*i])
	{
		if (!general->sg_quote && (*input)[*i] == '\"')
			general->db_quote = !general->db_quote;
		else if (!general->db_quote && (*input)[*i] == '\'')
			general->sg_quote = !general->sg_quote;
		else if ((*input)[*i] == '$' && !general->sg_quote)
		{
			open_dollar(general, *input, i, start);
			expand_var(input, general, &start, i);
			(--*i); //check this , do it only when after dollar comes $
		}
		else if (((*input)[*i] == ' ' || (*input)[*i] == '|' || (*input)[*i] == '>' || (*input)[*i] == '<') && !general->db_quote && !general->sg_quote)
		{
			if ((*input)[*i] == ' ')
				return (add_token_list(&general->tok_lst, my_substr(*input, start, (*i - start)), 0), 0);
			*i = init_op_token(*input, i, &general->tok_lst);
		}
		(*i)++;
	}
	add_token_list(&general->tok_lst, my_substr(*input, start, (*i - start)), 0);
	return (EXIT_SUCCESS);
}

// char *only_for_dol_harcakan(t_shell *general)
// {
//     char *status_str;

//     // Convert the exit status to a string
//     status_str = ft_itoa(get_exit_status());
//     // if (!status_str)
//     // {
//     //     fprintf(stderr, "Error: Failed to allocate memory for status_str.\n");
//     //     return NULL;
//     // }

//     // Set "?" as the key and status_str as the value in the doll_lst
//     general->doll_lst->u_key = ft_strdup("?");
//     if (!general->doll_lst->u_key)
//     {
//         fprintf(stderr, "Error: Failed to allocate memory for u_key.\n");
//         free(status_str);
//         return NULL;
//     }

//     general->doll_lst->value = status_str;
//     return (status_str);
// }
