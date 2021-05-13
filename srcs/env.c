/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 20:06:13 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/12 07:58:12 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*inc_shlvl(char *str, int i, long long shlvl)
{
	char	*tmp;
	char	*sh;

	tmp = get_value_var_env(str);
	if (tmp == NULL)
		shlvl = 0;
	else
	{
		if (check_is_num(tmp, i) == 1)
			shlvl = 0;
		else
			shlvl = ft_atoi(tmp);
	}
	if (shlvl < -1)
		shlvl = -1;
	else if (shlvl >= SHLVL_MIN && shlvl <= SHLVL_MAX)
		error_shlvl(&shlvl);
	else if (shlvl > SHLVL_MAX)
		shlvl = -1;
	if ((tmp = ft_itoa(shlvl + 1)) == NULL)
		return (NULL);
	sh = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	return (sh);
}

int		loop_copy_env(int init, int shlvl, char **envp, t_env *env)
{
	size_t	i;

	i = -1;
	while (++i < (env->size - 1))
	{
		if (shlvl == 0 && init == 1 && (i == env->size - 2))
			env->var_env[i] = ft_strdup("SHLVL=1");
		else if (ft_strncmp(envp[i], "SHLVL=", 6) == 0 && init == 1)
			env->var_env[i] = inc_shlvl(envp[i], 0, 0);
		else
			env->var_env[i] = ft_strdup(envp[i]);
		if (env->var_env[i] == NULL)
		{
			clear_env(env);
			return (error_msg(2, ' '));
		}
	}
	env->var_env[i] = NULL;
	return (0);
}

t_env	copy_env(char **envp, int init, size_t i)
{
	t_env	env;
	int		shlvl;

	shlvl = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			shlvl = 1;
		i++;
	}
	if (shlvl == 0 && init == 1)
		i++;
	env.size = i + 1;
	env.var_env = malloc(sizeof(char *) * (i + 1));
	if (env.var_env == NULL)
		return (env);
	if ((loop_copy_env(init, shlvl, envp, &env)) == -1)
		return (env);
	add_elt_env(&env);
	return (env);
}

t_env	init_env_null(void)
{
	t_env	env;

	env.var_env = malloc(sizeof(char *) * 2);
	if (env.var_env == NULL)
		return (env);
	env.var_env[0] = ft_strdup("SHLVL=1");
	if (env.var_env[0] == NULL)
	{
		error_msg(2, ' ');
		clear_env(&env);
		return (env);
	}
	env.var_env[1] = NULL;
	env.size = 2;
	add_elt_env(&env);
	return (env);
}
