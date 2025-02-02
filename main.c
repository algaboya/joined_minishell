/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:13 by etamazya          #+#    #+#             */
/*   Updated: 2025/02/02 14:02:01 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_shell	*general;

	(void)argv;
	input = NULL;
	general = (t_shell *)malloc(sizeof(t_shell));
	if (!general)
		return (EXIT_FAILURE);
	if (argc == 1)
	{
		init_general(general);
		create_env(env, general);
		set_shlvl(general);
		if (init_input(input, general))
			return (free(general), get_exit_status());
	}
	free(general);
	return (get_exit_status());
}
