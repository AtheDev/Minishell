/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 20:03:14 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/08 10:33:02 by adupuy           ###   ########.fr       */
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
	ret = loop_read(t, env);
//	prompt(t);
//	ret = get_next_line(0, &t->line);
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

	if (argc != 1)
		return (error_msg(6, ' '));
	void_arg_main(argc, argv);	
	init(&cmd_tmp, &cmd, &termcap);
	if (init2(&env, envp, &termcap) == 1)
		return (process_end_ko(&env, &termcap, cmd_tmp, cmd));
	while (env.exit == 0)
	{
		ret = loop_read_and_parsing(&env, &termcap, &cmd_tmp, &cmd);
		if (ret == 0)
			ret = save_cmd(&cmd, cmd_tmp);
//print_struct_complete(&cmd);
		if (ret == -1)
			return (process_end_ko(&env, &termcap, cmd_tmp, cmd));
		else if (ret == 0)
			process_shell(&env, &cmd, &cmd_tmp, &termcap);
		clear_last_struct(&env, &termcap, NULL/*cmd_tmp*/, cmd);
	}
	return (env.return_value);
}
