/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:14:25 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/28 11:51:17 by adupuy           ###   ########.fr       */
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
	t->history = NULL;
	t->tot_hist = 0;
	t->del_char = tgetstr("dc", NULL);
	t->del_line = tgetstr("dl", NULL);
	t->move_left = tgetstr("le", NULL);
	t->move_cursor = tgetstr("cm", NULL);
	return (0);		
}

void	init(t_list **cmd_tmp, t_list_cmd **cmd, t_termcap *t)
{
	*cmd_tmp = NULL;
	*cmd = NULL;
	t->line = NULL;
	t->input = NULL;
}
