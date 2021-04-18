/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:36:44 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/18 11:28:40 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_shell(t_env *env, t_list_cmd **cmd)
{
	t_list_cmd	*tmp;
	int	count;

	tmp = *cmd;
	count = 0;
	while (*cmd != NULL)
	{
		/*if ((*cmd)->pipe == 1)
		{
			count = count_pipes(cmd);
			exec_pipe(cmd, env, count);
		}
		else
		{*/
			if (dvlpmt_arg((*cmd)->arg_cmd, env) == -1)
				return (-1);
			/*if ((*cmd)->nb_redir != 0)
				process_redir_cmd(cmd, (*cmd)->nb_redir, env);
			redirect((*cmd)->fd[0], (*cmd)->fd[1]);
			if (is_builtin(env, cmd, 0) == 0)
				exec_pipe(cmd, env, 1);
			if ((*cmd)->nb_redir != 0)
				cancel_redirect(*cmd, env);*/
			*cmd = (*cmd)->next_cmd;
	//	}
	}
	*cmd = tmp;
//print_struct_complete(cmd);
	return (0);
}

