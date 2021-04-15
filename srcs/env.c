/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 20:06:13 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/15 22:46:13 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env(t_env *env)
{
	int	i;

	i = -1;
	while (env->var_env[++i] != NULL)
		free(env->var_env[i]);
	free(env->var_env);
	env->var_env = NULL;
}

void	add_elt_env(t_env *env)
{
	env->exit = 0;
	env->return_value = 0;
	env->tilde = get_value_var_env(get_var_env(&env, "HOME"));
	env->fd[0] = dup(0);
	env->fd[1] = dup(1);
}

char	*inc_shlvl(char *str)
{
	char	*tmp;
	char	*sh;
	int		shlvl;

	tmp = get_value_var_env(str);
	if (tmp == NULL)
		return (NULL);
	shlvl = ft_atoi(tmp);
	if ((tmp = ft_itoa(shlvl + 1)) == NULL)
		return (NULL);
	sh = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	return (sh);
}

t_env	copy_env(char **envp, int init, size_t i)
{
	t_env	env;

	while (envp[i] != NULL)
		i++;
	env.size = i;
	env.var_env = malloc(sizeof(char *) * (i + 1));
	if (env.var_env == NULL)
		return (env);
	i = -1;
	while (++i < env.size)
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0 && init == 1)
			env.var_env[i] = inc_shlvl(envp[i]);
		else
			env.var_env[i] = ft_strdup(envp[i]);
		if (env.var_env[i] == NULL)
		{
			error_msg(2, ' ');
			clear_env(&env);
			return (env);
		}
	}
	env.var_env[i] = NULL;
	add_elt_env(&env);
	return (env);
}
