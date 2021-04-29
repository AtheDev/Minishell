/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 20:03:14 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/29 15:19:23 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	void_arg_main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

void	clear_last_struct(t_env *env, t_termcap *t, t_list *cmd_tmp, t_list_cmd *cmd)
{
	process_end_ok(cmd_tmp, cmd);
	if (env->exit == 1)
	{
		clear_env(env);
		clear_termcap(t);
	}
}

int	loop_read_and_parsing(t_env *env, t_termcap *t, t_list **cmd_tmp, t_list_cmd **cmd)
{
	int	ret;

	init(cmd_tmp, cmd, t);
	if ((ret = loop_read(t)) == -1)
		return (process_end_ko(env, t, *cmd_tmp, *cmd));
	if (ret == 0)
		ret = analysis_input(&t->line, -1, cmd_tmp);
	if (ret == 1)
		env->return_value = 2;
	free(t->line);
	return (ret);
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
		ret = loop_read_and_parsing(&env, &termcap, &cmd_tmp, &cmd);
		if (ret == 0)
			ret = save_cmd(&cmd, cmd_tmp);
		if (ret == -1 )
			return (process_end_ko(&env, &termcap, cmd_tmp, cmd));
		else if (ret == 0)
			process_shell(&env, &cmd);
		clear_last_struct(&env, &termcap, cmd_tmp, cmd);
	}
	return (env.return_value);
}
