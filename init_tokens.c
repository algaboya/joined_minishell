/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 02:14:38 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 03:15:32 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_dollar_sign(char *input, int *i, t_token **token_list)
{
	if (input[*i] && input[*i] == '$')
	{
		if (input[*i + 1] && input[*i + 1] == '$')
			add_token_list(token_list, my_substr(input, *i, 2), 4);
		(*i)++;
		return (1);
	}
	return (0);
}

static int	check_pipe_sign(char *input, int *i, t_token **token_list)
{
	if (input[*i] && input[*i] == '|')
	{
		if (!input[*i + 1] || (input[*i + 1] != '|' && !input[*i + 2]))
			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
		if (input[*i + 1] == '|') // Handle `||` error
			return (printf("minisHell: syntax error near unexpected token `||'\n"), -1);
		add_token_list(token_list, my_substr(input, *i, 1), 1);
		return (1);
	}
	return (0);
}

static int	check_greater_than_sign(char *input, int *i, t_token **token_list)
{
	if (input[*i] && input[*i] == '>')
	{
		if (!input[*i + 1] || (input[*i + 1] != '<' && !input[*i + 2]))
			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);

		if (input[*i + 1] && input[*i + 1] == '>')
		{
			if (input[*i + 2] && (input[*i + 2] == '>' || input[*i + 2] == '<' || input[*i + 2] == '|'))
				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[*i + 2], input[*i + 3]), -1);
			add_token_list(token_list, my_substr(input, *i, 2), 4);
			(*i)++;
		}
		else if (input[*i + 1] && input[*i + 1] == '<')
		{
			return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[*i + 1], input[*i + 2]), -1);
		}
		else
			add_token_list(token_list, my_substr(input, *i, 1), 3);
		return (1);
	}
	return (0);
}

static int	check_less_than_sign(char *input, int *i, t_token **token_list)
{
	if (input[*i] && input[*i] == '<')
	{
		if (!input[*i + 1] || (input[*i + 1] != '>' && !input[*i + 2])) // Syntax error
			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
		if (input[*i + 1] && input[*i + 1] == '<')
		{
			if (input[*i + 2] && (input[*i + 2] == '>' || input[*i + 2] == '<'))
				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[*i + 2], input[*i + 3]), -1);
			add_token_list(token_list, my_substr(input, *i, 2), 5);
			(*i)++;
		}
		else
			add_token_list(token_list, my_substr(input, *i, 1), 2);
		return (1);
	}
	return (0);
}

int	init_op_token(char *input, int *i, t_token **token_list)
{
	if (!input || !token_list)
		return (-1);
	if (check_dollar_sign(input, i, token_list) == -1)
		return (-1);
	if (check_pipe_sign(input, i, token_list) == -1)
		return (-1);
	if (check_greater_than_sign(input, i, token_list) == -1)
		return (-1);
	if (check_less_than_sign(input, i, token_list) == -1)
		return (-1);
	return (*i);
}