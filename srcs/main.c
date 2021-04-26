/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 20:03:14 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/26 22:42:46 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sigint(int num)
{
	(void)num;
	if (g_sig != 0 && g_sig != 1)
		ft_putstr_fd("\n", 1);
	else
	{
		ft_putstr_fd("^C\n", 1);
	//	write(1, "^C\n", 3);
		prompt(NULL);
		g_sig = 1;
	}
}

void	handler_sigquit(int num)
{
	(void)num;
	if (g_sig != 0)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	t_list		*cmd_tmp;
	t_list_cmd	*cmd;
	t_termcap	termcap;
	int	ret;
	int	num = 0;

	init(argc, argv, &cmd_tmp, &cmd);
	if (init2(&env, envp, &termcap) == 1)
		return (process_end(&env, EXIT_FAILURE, cmd_tmp, cmd));
//	while (env.exit == 0)
	while (num < 4)
	{
		prompt(&termcap);
		swap_way_icanon_echo(0);
		ret = process_read(&termcap);
		termcap.line = NULL;
		cmd = NULL;
		cmd_tmp = NULL;
		if (termcap.history != NULL && ret != 2)
			termcap.line = ft_strdup(termcap.history->content);
		else
		{
			if ((termcap.line = malloc(sizeof(char))) == NULL)
				return (-1);
			termcap.line[0] = '\0';
		}

//printf("input = %s\n", termcap.history->content);
//print_hist(&termcap.history);
		swap_way_icanon_echo(1);
		num++;
	//	process_end(&env, EXIT_SUCCESS, cmd_tmp, cmd);
//		ret = get_next_line(0, &line);
//printf("1\n");
	/*	if (ret == -1)
			return (process_end(&env, EXIT_FAILURE, cmd_tmp, cmd));
		if (ret == 0)
			ret = analysis_input(&termcap.line, -1, &cmd_tmp);
		free(termcap.line);
		if (ret == -1 )
			return (process_end(&env, EXIT_FAILURE, cmd_tmp, cmd));
		if (ret == 0)
			ret = save_cmd(&cmd, cmd_tmp);
		if (ret == -1)
			return (process_end(&env, EXIT_FAILURE, cmd_tmp, cmd));
		else
			process_shell(&env, &cmd);
		process_end(&env, EXIT_SUCCESS, cmd_tmp, cmd);
		if (env.exit == 1)
			clear_env(&env);*/
	}
//	print_hist(&termcap.history);
	return (env.return_value);
}
