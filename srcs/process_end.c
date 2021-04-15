/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:16:56 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/15 23:25:36 by adupuy           ###   ########.fr       */
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

	while (cmd->next_cmd != NULL)
	{
		tmp = cmd->next_cmd;
		i = 0;
		while (cmd->arg_cmd[i] != NULL)
		{
			free(cmd->arg_cmd[i]);
			i++;
		}
		free(cmd->arg_cmd);
		free(cmd);
		cmd = tmp;
	}
	i = 0;
	while (cmd->arg_cmd[i] != NULL)
	{
		free(cmd->arg_cmd[i]);
		i++;
	}
	free(cmd->arg_cmd);
	free(cmd);
}

int		process_end(t_env *env, int end, t_list *cmd_tmp)
{
	clear_env(env);
	if (cmd_tmp != NULL)
		clear_cmd_tmp(cmd_tmp);
	return (end);
}
