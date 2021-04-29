/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 10:16:44 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/30 00:26:37 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_env *env, t_list_cmd **cmd, int fork)
{
	int	ret;

	ret = 3;
	if (ft_strncmp((*cmd)->arg_cmd[0], "exit", 5) == 0)
		ft_exit((*cmd)->arg_cmd, &env, fork);
	else
	{
	env->return_value = 0;
	if (ft_strncmp((*cmd)->arg_cmd[0], "echo", 5) == 0)
		ret = ft_echo((*cmd)->arg_cmd, 1, 0);		// 0
	else if (ft_strncmp((*cmd)->arg_cmd[0], "pwd", 4) == 0)
		ret = ft_pwd((*cmd)->arg_cmd, env);		// 0 || 1
	else if (ft_strncmp((*cmd)->arg_cmd[0], "env", 4) == 0)
		ret = ft_env((*cmd)->arg_cmd, env);		// 0 || 1($?127)
	else if (ft_strncmp((*cmd)->arg_cmd[0], "unset", 6) == 0)
		ret = ft_unset((*cmd)->arg_cmd, &env);		// 0 || 1 || -1
	else if (ft_strncmp((*cmd)->arg_cmd[0], "export", 7) == 0)
		ret = ft_export((*cmd)->arg_cmd, &env);		// 0 || 1 || -1
	else if (ft_strncmp((*cmd)->arg_cmd[0], "cd", 3) == 0)
		ret = ft_cd((*cmd)->arg_cmd, &env);		// A refaire
	else 
		return (1);
	}
	if (ret != 3)
		env->return_value = ret;
	if (fork == 1)
		exit(env->return_value);
	return (0);
}
