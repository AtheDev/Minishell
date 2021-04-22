/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:50:11 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/21 14:59:00 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_pipes(t_list_cmd **cmd)
{
	t_list_cmd	*tmp;
	int			count;

	tmp = *cmd;
	count = 0;
	while ((*cmd)->pipe == 1 && (*cmd)->next_cmd != NULL)
	{
		count++;
		*cmd = (*cmd)->next_cmd;
	}
	count++;
	*cmd = tmp;
	return (count);
}

int		create_pipe(t_list_cmd *cmd1, t_list_cmd *cmd2)
{
	int	fd[2];
	int	ret;

	ret = pipe(fd);
	if (ret == 0)
	{
		cmd1->fd[1] = fd[1];
		cmd2->fd[0] = fd[0];
		return (0);
	}
	else
		return (-1);
}

void	redirect(int fd1, int fd2)
{
	if (fd1 != 0)
	{
		if (dup2(fd1, 0) != -1)
			close(fd1);
	}
	if (fd2 != 1)
	{
		if (dup2(fd2, 1) != -1)
			close(fd2);
	}
}

void	cancel_redirect(t_list_cmd *cmd, t_env *env)
{
	int	i;

	close(cmd->fd[0]);
	close(cmd->fd[1]);
	cmd->fd[0] = 0;
	cmd->fd[1] = 0;
	dup2(env->fd[0], 0);
	dup2(env->fd[1], 1);
	i = -1;
	while (++i < cmd->nb_redir)
		close(cmd->fd_redir[i]);
}
