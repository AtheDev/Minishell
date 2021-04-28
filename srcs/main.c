/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 20:03:14 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/28 16:48:39 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	void_arg_main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	t_list	*cmd_tmp;
	t_list_cmd	*cmd;
	t_termcap	termcap;
	int	ret;
	int num = -1;

	void_arg_main(argc, argv);
	init(&cmd_tmp, &cmd, &termcap);
	if (init2(&env, envp, &termcap) == 1)
		return (process_end_ko(&env, &termcap, cmd_tmp, cmd));
	while (++num < 4 && env.exit == 0)
	{
		init(&cmd_tmp, &cmd, &termcap);
		if ((ret = loop_read(&termcap)) == -1)
			return (process_end_ko(&env, &termcap, cmd_tmp, cmd));
		if (ret == 0 /*tout est OK avec input*/|| ret == 2 /*input vide*/)
			ret = analysis_input(&termcap.line, -1, &cmd_tmp);
		free(termcap.line);
		if (ret == 1)
			continue ;
		else if (ret == -1 )
			return (process_end_ko(&env, &termcap, cmd_tmp, cmd));
		else if (ret == 0)
			ret = save_cmd(&cmd, cmd_tmp);
		if (ret == -1)
			return (process_end_ko(&env, &termcap, cmd_tmp, cmd));
		else
			process_shell(&env, &cmd);
		process_end_ok(cmd_tmp, cmd);
		if (env.exit == 1)
		{	clear_env(&env);
			clear_termcap(&termcap);}
	}
	return (env.return_value);
}
