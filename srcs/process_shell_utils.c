/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shell_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:25:29 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/12 22:27:06 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		search_last_return_value(int nb_cmd, int tab_pid[nb_cmd][2])
{
	int	i;
	int	pid;
	int	ret;

	i = -1;
	ret = 0;
	pid = 0;
	while (++i < nb_cmd)
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

void	return_wait(t_env *env, int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		env->return_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		env->return_value = WTERMSIG(status) + 128;
	g_sig.sig = 0;
}

int		exec_sh(t_list_cmd *cmd, t_env *env, t_termcap *t, t_list_cmd **tmp)
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
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->arg_cmd[0], 2);
			write(2, ": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 1);
		}
		env->return_value = 1;
		process_end_ko(env, t, NULL, *tmp);
		exit(1);
		return (1);
	}
	return (0);
}
