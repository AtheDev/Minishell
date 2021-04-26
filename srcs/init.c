/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:14:25 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/26 17:54:03 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init2(t_env *env, char **envp, t_termcap *t)
{
	g_sig = 0;
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, handler_sigquit);
	*env = copy_env(envp, 1, 0);
	if (env->var_env == NULL)
		return (1);
	if (init_term(env) != 0)
		return (1);
	t->input = NULL;
	t->history = NULL;
	t->tot_hist = 0;
	t->del_char = tgetstr("dc", NULL);
	t->del_line = tgetstr("dl", NULL);
	t->move_left = tgetstr("le", NULL);
//	if (swap_way_icanon_echo(0) == -1)
//		return (1);
	return (0);		
}

void	init(int argc, char **argv, t_list **cmd_tmp, t_list_cmd **cmd)
{
	(void)argc;
	(void)argv;
	*cmd_tmp = NULL;
	*cmd = NULL;
}
