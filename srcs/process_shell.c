/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:36:44 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/13 11:13:19 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_pipe_cmd_next
	(t_list_cmd *cmd, t_env *env, t_termcap *t, t_list_cmd **tmp)
{
	int	ret;

	ret = 0;
	if (cmd->nb_redir > 0)
		ret = process_redir_cmd(&cmd, cmd->nb_redir, 0, 0);
	if (ret == -1 || ret == 1)
	{
		process_end_ko(env, t, NULL, *tmp);
		exit(ret);
		return (ret);
	}
	redirect(cmd->fd[0], cmd->fd[1]);
	if (is_builtin(env, &cmd, 1, tmp) == 1)
		env->return_value = exec_sh(cmd, env, t, tmp);
	process_end_ko(env, t, NULL, *tmp);
	return (env->return_value);
}

void	exec_pipe_cmd
	(t_list_cmd **cmd, t_env *env, int nb_cmd, t_list_cmd **tmp)
{
	pid_t	pid;
	int		save_nb_cmd;

	save_nb_cmd = nb_cmd;
	while (nb_cmd > 0)
	{
		if ((*cmd)->nb_redir == 0)
			if (((*cmd)->arg_cmd = dvlpmt_arg((*cmd)->arg_cmd, env)) == NULL)
				return ;
		if (nb_cmd - 1 != 0)
			create_pipe(*cmd, (*cmd)->next_cmd);
		errno = 0;
		if ((pid = fork()) == -1)
			strerror(errno);
		else if (pid == 0)
			exec_pipe_cmd_next(*cmd, env, &g_sig.t, tmp);
		else
		{
			cancel_redirect(*cmd, env, 1);
			*cmd = (*cmd)->next_cmd;
			nb_cmd--;
		}
	}
	g_sig.sig = 3;
	wait_with_pipe(env, save_nb_cmd);
}

void	exec_one_cmd
	(t_list_cmd **cmd, t_env *env, t_termcap *t, t_list_cmd **tmp)
{
	pid_t	pid;

	errno = 0;
	if ((pid = fork()) == -1)
		strerror(errno);
	else if (pid == 0)
	{
		exec_sh(*cmd, env, t, tmp);
		exit(env->return_value);
	}
	else
	{
		g_sig.sig = 2;
		return_wait(env, pid);
	}
}

int		simple_cmd
	(t_env *env, t_list_cmd **cmd, t_termcap *t, t_list_cmd **tmp)
{
	int	ret;

	ret = 0;
	if ((*cmd)->nb_redir == 0)
	{
		if (((*cmd)->arg_cmd = dvlpmt_arg((*cmd)->arg_cmd, env)) == NULL)
			return (-1);
	}
	if ((*cmd)->nb_redir != 0)
		ret = process_redir_cmd(cmd, (*cmd)->nb_redir, 0, 0);
	if (ret == 0)
	{
		redirect((*cmd)->fd[0], (*cmd)->fd[1]);
		if ((*cmd)->arg_cmd[0] != NULL)
		{
			if (is_builtin(env, cmd, 0, tmp) == 1)
				exec_one_cmd(cmd, env, t, tmp);
		}
	}
	if ((*cmd)->nb_redir != 0)
		cancel_redirect(*cmd, env, 0);
	return (ret);
}

int		process_shell
	(t_env *env, t_list_cmd **cmd, t_list **cmd_tmp, t_termcap *t)
{
	t_list_cmd	*tmp;
	int			nb_cmd;
	int			ret;

	clear_cmd_tmp(*cmd_tmp);
	ret = 0;
	tmp = *cmd;
	nb_cmd = 0;
	while (*cmd != NULL)
	{
		if ((*cmd)->pipe == 1)
		{
			nb_cmd = count_pipes(cmd);
			exec_pipe_cmd(cmd, env, nb_cmd, &tmp);
		}
		else
		{
			ret = simple_cmd(env, cmd, t, &tmp);
			if (ret == -1)
				break ;
			*cmd = (*cmd)->next_cmd;
		}
	}
	*cmd = tmp;
	return (ret);
}
