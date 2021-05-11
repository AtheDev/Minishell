/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:16:56 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/11 11:33:25 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **arg, t_env *env)
{
	int	i;

	i = 0;
	if (arg[1] != NULL)
		return (error_msg_with_string(7, arg[1]));
	else
	{
		while (env->var_env[i] != NULL)
		{
			if (ft_strchr(env->var_env[i], '=') != NULL)
				printf("%s\n", env->var_env[i]);
			i++;
		}	
	}
	return (0);
}
