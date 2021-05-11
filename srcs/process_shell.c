/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:36:44 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/11 10:51:08 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_last_return_value(int nb_cmd, int tab_pid[nb_cmd][2])
{
	int	i;
	int	pid;
	int	ret;

	i = -1;
	ret = 0;
	pid = 0;
	while(++i < nb_cmd)
	{
		if (pid < tab_pid[i][0])
		{
			pid = tab_pid[i][0];
			ret = tab_pid[i][1];
		}
	}
	return (ret);
}

void	wait_with_pipe(t_env *env, int nb_cmd)
{
	int	status;
	int	tab_pid[nb_cmd][2];
	int	i;
	int	pid;

	i = 0;
	pid = 0;
	while (pid >= 0)
	{
		pid = waitpid(-1, &status, 0);
		tab_pid[i][0] = pid;
		if (WIFEXITED(status))
			env->return_value = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			env->return_value = WTERMSIG(status) + 128;
		tab_pid[i][1] = env->return_value;
		i++;
	}
	env->return_value = search_last_return_value(nb_cmd, tab_pid);
	g_sig.sig = 0;
}

void	return_wait(t_env *env, int pid/*, int num*/)
{
	int	status;

/*	if (num == 1)
		while (wait(&status) > 0);
	else if (num == 0)*/
//	{
		do {
			waitpid(pid, &status, /*WUNTRACED | WCONTINUED*/0);
			if (WIFEXITED(status))
				env->return_value = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				env->return_value = WTERMSIG(status) + 128;
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
//	}
//	else
//		while (wait(&status) > 0);
/*	if (WIFEXITED(status))
		env->return_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		env->return_value = WTERMSIG(status) + 128;*/
	g_sig.sig = 0;
}

int	exec_sh(t_list_cmd *cmd, t_env *env, t_termcap *t, t_list_cmd **tmp)
{
	int	ret;

	if ((ret = search_path(cmd->arg_cmd, &env, 1)) != 0)
	{
		process_end_ko(env, t, NULL, *tmp);
		exit(env->return_value);
		return (1);
	}
	else
	{
		errno = 0;
		if (execve(cmd->arg_cmd[0], cmd->arg_cmd, env->var_env) == -1)
			ft_putstr_fd(strerror(errno), 2);
		env->return_value = 1;
		process_end_ko(env, t, NULL, *tmp);
		exit(1);
		return (1);
	}
	return (0);
}

int	exec_pipe_cmd_next(t_list_cmd *cmd, t_env *env, t_termcap *t, t_list_cmd **tmp)
{
	int	ret;

	ret = 0;
	if (cmd->nb_redir > 0)
		ret = process_redir_cmd(&cmd, cmd->nb_redir);
	if (ret == -1 || ret == 1)
	{
		process_end_ko(env, t, NULL, *tmp);
		exit(ret);
		return (ret);		// A revoir pour mettre exit();
	}
	redirect(cmd->fd[0], cmd->fd[1]);
	if (is_builtin(env, &cmd, 1, t, tmp) == 1)
		env->return_value = exec_sh(cmd, env, t, tmp);
	process_end_ko(env, t, NULL, *tmp);
	return (env->return_value);
}

void	exec_pipe_cmd(t_list_cmd **cmd, t_env *env, int nb_cmd, t_termcap *t, t_list_cmd **tmp)
{
	pid_t	pid;
	int	save_nb_cmd;

	save_nb_cmd = nb_cmd;
	while (nb_cmd > 0)
	{
		if ((*cmd)->nb_redir == 0)
		{
			if (((*cmd)->arg_cmd = dvlpmt_arg((*cmd)->arg_cmd, env)) == NULL)
				return ;
		}
		if (nb_cmd - 1 != 0)
			create_pipe(*cmd, (*cmd)->next_cmd);
		errno = 0;
		if ((pid = fork()) == -1)
			strerror(errno);
		else if (pid == 0)
			exec_pipe_cmd_next(*cmd, env, t, tmp);
		else
		{
			cancel_redirect(*cmd, env, 1);
			*cmd = (*cmd)->next_cmd;
			nb_cmd--;
		}
	}
	g_sig.sig = 3;
//	return_wait(env, -1, 1);
	wait_with_pipe(env, save_nb_cmd);
}

void	exec_one_cmd(t_list_cmd **cmd, t_env *env, t_termcap *t, t_list_cmd **tmp)
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

int	process_shell(t_env *env, t_list_cmd **cmd, t_list **cmd_tmp, t_termcap *t)
{
	t_list_cmd	*tmp;
	int	nb_cmd;
	int	ret;

	clear_cmd_tmp(*cmd_tmp);
	cmd_tmp = NULL;
	ret = 0;
	tmp = *cmd;
	nb_cmd = 0;
	while (*cmd != NULL)
	{
		if ((*cmd)->pipe == 1)
		{
			nb_cmd = count_pipes(cmd);
			exec_pipe_cmd(cmd, env, nb_cmd, t, &tmp);
		}
		else
		{
			if ((*cmd)->nb_redir == 0)
			{
				if (((*cmd)->arg_cmd = dvlpmt_arg((*cmd)->arg_cmd, env/*, cmd*/)) == NULL)
					return (-1);
			}
//print_struct_complete(cmd);
			if ((*cmd)->nb_redir != 0)
				ret = process_redir_cmd(cmd, (*cmd)->nb_redir);
			if (ret != 1)
			{
				redirect((*cmd)->fd[0], (*cmd)->fd[1]);
				if ((*cmd)->arg_cmd[0] != NULL)
				{
					if (is_builtin(env, cmd, 0, t, &tmp) == 1)
						exec_one_cmd(cmd, env, t, &tmp);
				}
			}
			if ((*cmd)->nb_redir != 0)
				cancel_redirect(*cmd, env, 0);
			*cmd = (*cmd)->next_cmd;
		}
	}
	*cmd = tmp;
//print_struct_complete(cmd);
	return (0);
}

