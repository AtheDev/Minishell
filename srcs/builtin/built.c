/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 10:16:44 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/21 14:35:47 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_env *env, t_list_cmd **cmd, int fork)
{
	if (ft_strncmp((*cmd)->arg_cmd[0], "echo", 5) == 0)
		ft_echo((*cmd)->arg_cmd, 1, 0);
	else if (ft_strncmp((*cmd)->arg_cmd[0], "pwd", 4) == 0)
		ft_pwd((*cmd)->arg_cmd, env);
	else if (ft_strncmp((*cmd)->arg_cmd[0], "env", 4) == 0)
		ft_env((*cmd)->arg_cmd, env);
	else if (ft_strncmp((*cmd)->arg_cmd[0], "unset", 6) == 0)
		ft_unset((*cmd)->arg_cmd, &env);
	else if (ft_strncmp((*cmd)->arg_cmd[0], "export", 7) == 0)
		ft_export((*cmd)->arg_cmd, &env);
	else if (ft_strncmp((*cmd)->arg_cmd[0], "cd", 3) == 0)
		ft_cd((*cmd)->arg_cmd, &env);
	else if (ft_strncmp((*cmd)->arg_cmd[0], "exit", 5) == 0)
		ft_exit((*cmd)->arg_cmd, &env, fork);
	else
		return (1);
/*	if (ft_strncmp((*cmd)->arg_cmd[0], "exit", 5) == 0)
		return (env->return_value);*/
	if (fork == 1)
		exit(env->return_value);
	return (0);
}
