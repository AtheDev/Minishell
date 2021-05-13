/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 20:03:14 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/12 21:57:11 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	void_arg_main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

void	clear_last_struct
	(t_env *env, t_termcap *t, t_list *cmd_tmp, t_list_cmd *cmd)
{
	process_end_ok(cmd_tmp, cmd);
	if (env->exit == 1)
	{
		clear_env(env);
		clear_termcap(t);
	}
}

int		loop_read_and_parsing
	(t_env *env, t_termcap *t, t_list **cmd_tmp, t_list_cmd **cmd)
{
	int	ret;

	init(cmd_tmp, cmd, t);
	ret = loop_read(t, env);
	if (ret == -1)
		return (process_end_ko(env, t, *cmd_tmp, *cmd));
	else if (ret == -2)
	{
		ft_putstr_fd("exit\n", 1);
		env->return_value = 0;
		env->exit = 1;
	}
	if (ret == 0)
		ret = analysis_input(&t->line, -1, cmd_tmp);
	if (ret == 1)
	{
		clear_cmd_tmp(*cmd_tmp);
		env->return_value = 2;
	}
	free(t->line);
	return (ret);
}

int		main(int argc, char **argv, char **envp)
{
	t_list		*cmd_tmp;
	t_list_cmd	*cmd;
	int			ret;

	if (argc != 1)
		return (error_msg(6, ' '));
	void_arg_main(argc, argv);
	init(&cmd_tmp, &cmd, &g_sig.t);
	if (init2(&g_sig.env, envp, &g_sig.t) == 1)
		return (process_end_ko(&g_sig.env, &g_sig.t, cmd_tmp, cmd));
	while (g_sig.env.exit == 0)
	{
		ret = loop_read_and_parsing(&g_sig.env, &g_sig.t, &cmd_tmp, &cmd);
		if (ret == 0)
			ret = save_cmd(&cmd, cmd_tmp);
		if (ret == -1)
			return (process_end_ko(&g_sig.env, &g_sig.t, cmd_tmp, cmd));
		else if (ret == 0)
			ret = process_shell(&g_sig.env, &cmd, &cmd_tmp, &g_sig.t);
		if (ret == -1)
			return (process_end_ko(&g_sig.env, &g_sig.t, cmd_tmp, cmd));
		clear_last_struct(&g_sig.env, &g_sig.t, NULL, cmd);
	}
	return (g_sig.env.return_value);
}
