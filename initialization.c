/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:08 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 05:38:17 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_general(t_shell *general)
{
	general->tok_lst = NULL;
	general->env_lst = NULL;
	general->cmd_lst = NULL;
	general->doll_lst = (t_dollar *)malloc(sizeof(t_dollar));
	general->sorted_env_lst = NULL;
	general->sg_quote = 0;
	general->db_quote = 0;
	general->pipe_index = 0;
	general->pipe_count = 0;
	general -> original_stdin = dup(STDIN_FILENO);
	general -> original_stdout = dup(STDOUT_FILENO);
}

int	init_input(char *input, t_shell *general)
{
	static int	index;

	while (1)
	{
		index = 0;
		init_signal(1);
		input = readline("\033[38;5;51m\033[48;5;16mminisHell:\033[0m ");
		if (input && input[0] != '\0')
		{
			add_history(input);
			if (init_tokens_cmds(input, general, 0) == 0)
			{
				execution(general, index);
				cmd_free(general);
				close_pipes(general->fd, general->pipe_count);
			}
			free(input);
		}
		else if (input && input[0] == '\0')
			free(input);
		else if (!input)
			clean_gen_exit(general, get_exit_status(), 0, 1);
		free_fd(general);
	}
	return (free(input), get_exit_status());
}

static void	skip_whitespace(char *input, int *i)
{
	while ((input[*i] >= 9 && input[*i] <= 13) || input[*i] == 32)
		(*i)++;
}

int	init_tokens_cmds(char *input, t_shell *general, int i)
{
	int	start;
	int	flag;

	flag = 0;
	// while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
	// 	i++;
	skip_whitespace(input, &i);
	while (flag >= 0 && input[i] != '\0')
	{
		if (flag >= 0 && input[i] && (input[i] == '|' || input[i] == '>'
				|| input[i] == '<' || input[i] == ' '))
			flag = init_op_token(input, &i, &general->tok_lst);
		else
		{
			start = i;
			while (flag >= 0 && input[i] && input[i] != '|' && input[i] != '>'
				&& input[i] != '<' && input[i] != ' ' && input[i] != '$'
				&& input[i] != 34 && input[i] != 39)
				i++;
			if (input[i] && flag >= 0)
				flag = check_cut_quotes(general, &input, &i, start);
			else if (i > start)
				add_token_list(&general->tok_lst, my_substr((const char *)input,
						start, i - start), 0);
			i--;
		}
		if (flag < 0)
			return (clean_list(&general->tok_lst), -1);
		if (input[i])
			i++;
	}
	general->tok_lst = remove_extra_quotes(general);
	check_heredoc_limit(general);
	create_cmd_lst(general);
	clean_list(&general->tok_lst);
	return (0);
}

t_cmd_lst	*initialize_new_cmd(void)
{
	t_cmd_lst	*new_cmd;

	new_cmd = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	new_cmd->cmd = NULL;
	new_cmd->args = NULL;
	new_cmd->next = NULL;
	new_cmd->heredoc = NULL;
	new_cmd->red_in = NULL;
	new_cmd->red_out = NULL;
	new_cmd->red_append = NULL;
	new_cmd->std_in = -2;
	new_cmd->std_out = -2;
	return (new_cmd);
}
