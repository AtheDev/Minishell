/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:10:10 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/29 22:46:52 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg_var(char **arg, int cmd)
{
	int	i;

	i = 0;
	if (ft_isdigit((*arg)[i]) == 1)
		return (1);
	while ((*arg)[i] != '\0')
	{
		if (ft_isalnum((*arg)[i]) == 0 && (*arg)[i] != '_')
		{
			if ((*arg)[i] == '=' && cmd == 1 && i > 0)
				return (0);
			return (1);
		}
		i++;
	}
	if (cmd == 1)
		return (-1);
	return (0);
}

int	ft_unset(char **arg, t_env **env)
{
	int	i;

	i = 1;
	if (arg[i] != NULL)
	{
		while (arg[i] != NULL)
		{
			if (check_arg_var(&arg[i], 0) == 0)
			{
				if (process_delete_var_env(arg[i], env) != 0)
					return (error_msg(2, ' '));
			}
			else
				error_msg_with_string(5, arg[i]);
			i++;
		}
	}
	return (0);
}
