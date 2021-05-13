/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 07:32:39 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/12 07:42:22 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_shlvl(long long *shlvl)
{
	ft_putstr_fd("minishell: warning : shell level too high (", 2);
	ft_putnbr_fd(*shlvl, 2);
	ft_putstr_fd("), initialization to 1\n", 2);
	*shlvl = 0;
}

void	clear_env(t_env *env)
{
	int	i;

	i = -1;
	while (env->var_env[++i] != NULL)
		free(env->var_env[i]);
	free(env->var_env);
	env->var_env = NULL;
	close(env->fd[0]);
	close(env->fd[1]);
}

void	add_elt_env(t_env *env)
{
	env->exit = 0;
	env->return_value = 0;
	env->fd[0] = dup(0);
	env->fd[1] = dup(1);
}

int		check_is_num(char *str, int i)
{
	if (str[i] == ' ')
	{
		while (str[i] == ' ' && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			return (1);
		i++;
	}
	while (str[i] != ' ' && str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	if (str[i] == ' ')
	{
		i++;
		while (str[i] != '\0')
		{
			if (ft_isspace(str[i]) == 0)
				return (1);
			i++;
		}
	}
	return (0);
}
