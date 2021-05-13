/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:16:56 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/12 22:00:25 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_cmd_tmp(t_list *cmd)
{
	t_list	*lst;

	lst = NULL;
	while (cmd != NULL)
	{
		lst = cmd->next;
		free(cmd->content);
		free(cmd);
		cmd = lst;
	}
	cmd = NULL;
}

void	clear_cmd(t_list_cmd *cmd)
{
	t_list_cmd	*tmp;
	int			i;

	while (cmd != NULL)
	{
		tmp = cmd->next_cmd;
		i = 0;
		while (cmd->arg_cmd[i] != NULL)
		{
			free(cmd->arg_cmd[i]);
			i++;
		}
		free(cmd->arg_cmd);
		cmd->arg_cmd = NULL;
		if (cmd->fd_redir != NULL)
			free(cmd->fd_redir);
		free(cmd);
		cmd = tmp;
	}
}

void	clear_termcap(t_termcap *t)
{
	if (t->history != NULL)
	{
		clear_cmd_tmp(t->history);
		t->history = NULL;
	}
	t->save_prompt = ft_free(t->save_prompt);
	t->save_oldpwd = ft_free(t->save_oldpwd);
	t->save_pwd = ft_free(t->save_pwd);
	t->save_home = ft_free(t->save_home);
}

int		process_end_ko(t_env *env, t_termcap *t,
		t_list *cmd_tmp, t_list_cmd *cmd)
{
	clear_env(env);
	clear_termcap(t);
	if (cmd_tmp != NULL)
		clear_cmd_tmp(cmd_tmp);
	cmd_tmp = NULL;
	if (cmd != NULL)
		clear_cmd(cmd);
	cmd = NULL;
	return (EXIT_FAILURE);
}

int		process_end_ok(t_list *cmd_tmp, t_list_cmd *cmd)
{
	if (cmd_tmp != NULL)
		clear_cmd_tmp(cmd_tmp);
	cmd_tmp = NULL;
	if (cmd != NULL)
		clear_cmd(cmd);
	cmd = NULL;
	return (EXIT_SUCCESS);
}
