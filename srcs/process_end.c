/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:16:56 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/28 15:44:09 by adupuy           ###   ########.fr       */
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
}

int		process_end(t_env *env, int end, t_list *cmd_tmp, t_list_cmd *cmd)
{
	if (end == EXIT_FAILURE)
		clear_env(env);
	if (cmd_tmp != NULL)
		clear_cmd_tmp(cmd_tmp);
	cmd_tmp = NULL;
	if (cmd != NULL)
		clear_cmd(cmd);
	cmd = NULL;
	return (end);
}
