/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 20:06:13 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/11 17:34:04 by adupuy           ###   ########.fr       */
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

char	*inc_shlvl(char *str)
{
	char	*tmp;
	char	*sh;
	long long		shlvl;

	tmp = get_value_var_env(str);
	if (tmp == NULL)
		shlvl = 0;
	else if (ft_str_digit(tmp) == 1)
		shlvl = 0;
	else
		shlvl = ft_atoi(tmp);
	if (shlvl < -1)
		shlvl = -1;
	else if (shlvl >= SHLVL_MIN && shlvl <= SHLVL_MAX)
	{
		ft_putstr_fd("minishell: warning : shell level too high (", 2);
		ft_putnbr_fd(shlvl + 1, 2);
		ft_putstr_fd("), initialization to 1\n", 2);
		shlvl = 0;
	}
	else if (shlvl > SHLVL_MAX)
		shlvl = -1;
	if ((tmp = ft_itoa(shlvl + 1)) == NULL)
		return (NULL);
	sh = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	return (sh);
}

t_env	copy_env(char **envp, int init, size_t i)
{
	t_env	env;
	int	shlvl;

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
	i = -1;
	while (++i < (env.size - 1))
	{
		if (shlvl == 0 && init == 1 && (i == env.size - 2))
			env.var_env[i] = ft_strdup("SHLVL=1");
		else if (ft_strncmp(envp[i], "SHLVL=", 6) == 0 && init == 1)
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
