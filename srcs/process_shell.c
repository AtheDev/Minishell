/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:36:44 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/01 14:49:32 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	return_wait(t_env *env, int cpid)
{
	int	status = 0;

	do {
		waitpid(cpid, &status, WUNTRACED | WCONTINUED);
		if (WIFEXITED(status))
			env->return_value = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			env->return_value = WTERMSIG(status) + 128;
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	g_sig = 0;
}

int	exec_sh(t_list_cmd *cmd, t_env *env, t_termcap *t)
{
	int	ret;

	if ((ret = search_path(cmd->arg_cmd, &env, 1)) != 0)
	{
		process_end_ko(env, t, NULL, cmd);
		exit(env->return_value);
		return (1);
	}
	else
	{
		errno = 0;
		if (execve(cmd->arg_cmd[0], cmd->arg_cmd, env->var_env) == -1)
			strerror(errno);
		env->return_value = 1;
		exit(1);
		return (1);
	}
	return (0);
}

int	exec_pipe_cmd_next(t_list_cmd *cmd, t_env *env, t_termcap *t)
{
	int	ret;

	ret = 0;
	if (cmd->nb_redir > 0)
		ret = process_redir_cmd(&cmd, cmd->nb_redir);
	if (ret == -1 || ret == 1)
		return (ret);		// A revoir pour mettre exit();
	redirect(cmd->fd[0], cmd->fd[1]);
	if (is_builtin(env, &cmd, 1, t) == 1)
		env->return_value = exec_sh(cmd, env, t);
	return (env->return_value);
}

void	exec_pipe_cmd(t_list_cmd **cmd, t_env *env, int nb_cmd, t_termcap *t)
{
	pid_t	pid;

	while (nb_cmd > 0)
	{
		if (dvlpmt_arg((*cmd)->arg_cmd, env) == -1)
			return ;
		if (nb_cmd - 1 != 0)
			create_pipe(*cmd, (*cmd)->next_cmd);
		errno = 0;
		if ((pid = fork()) == -1)
			strerror(errno);
		else if (pid == 0)
			exec_pipe_cmd_next(*cmd, env, t);
		else
		{
			cancel_redirect(*cmd, env, 1);
			return_wait(env, pid);
			*cmd = (*cmd)->next_cmd;
			nb_cmd--;
		}
	}
	g_sig = 2;
//	return_wait(env, -1);
	
}

void	exec_one_cmd(t_list_cmd **cmd, t_env *env, t_termcap *t)
{
	pid_t	pid;

	errno = 0;
	if ((pid = fork()) == -1)
		strerror(errno);
	else if (pid == 0)
	{
		exec_sh(*cmd, env, t);
		exit(env->return_value);
	}
	else
	{
		g_sig = 2;
		return_wait(env, pid);
	}
}

int	process_shell(t_env *env, t_list_cmd **cmd, t_list **cmd_tmp, t_termcap *t)
{(void)t;
	t_list_cmd	*tmp;
	int	nb_cmd;
clear_cmd_tmp(*cmd_tmp);
*cmd_tmp = NULL;
	tmp = *cmd;
	nb_cmd = 0;
	while (*cmd != NULL)
	{
		if ((*cmd)->pipe == 1)
		{
			nb_cmd = count_pipes(cmd);
			exec_pipe_cmd(cmd, env, nb_cmd, t);
		}
		else
		{
			if (dvlpmt_arg((*cmd)->arg_cmd, env) == -1)
				return (-1);
			if ((*cmd)->nb_redir != 0)
				process_redir_cmd(cmd, (*cmd)->nb_redir);
			redirect((*cmd)->fd[0], (*cmd)->fd[1]);
			if (is_builtin(env, cmd, 0, t) == 1)
				exec_one_cmd(cmd, env, t);
			if ((*cmd)->nb_redir != 0)
				cancel_redirect(*cmd, env, 0);
			*cmd = (*cmd)->next_cmd;
		}
	}
	*cmd = tmp;
//print_struct_complete(cmd);
	return (0);
}

