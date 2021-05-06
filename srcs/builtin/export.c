/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:45:29 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/06 19:18:38 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	swap_env(t_env *cp_env, int *i, char *tmp)
{
	if (ft_strncmp(cp_env->var_env[*i + 1], cp_env->var_env[*i],
	ft_strlen(cp_env->var_env[*i])) < 0)
	{
		if ((tmp = ft_strdup(cp_env->var_env[*i])) == NULL)
		{
			free_tab_string(cp_env->var_env);
			return (-1);
		}
		free(cp_env->var_env[*i]);
		if ((cp_env->var_env[*i] = ft_strdup(cp_env->var_env[*i + 1])) == NULL)
		{
			free(tmp);
			free_tab_string(cp_env->var_env);
			return (-1);
		}
		free(cp_env->var_env[*i + 1]);
		if ((cp_env->var_env[*i + 1] = ft_strdup(tmp)) == NULL)
		{
			free(tmp);
			free_tab_string(cp_env->var_env);
			return (-1);
		}
		*i = 0;
	}
	else
		(*i)++;
	tmp = ft_free(tmp);
	return (0);
}

int	sort_env(t_env **env, int i)
{
	t_env	cp_env;
	char	*tmp;

	cp_env = copy_env((*env)->var_env, 0, 0);
	if (cp_env.var_env == NULL)
		return (-1);
	tmp = NULL;
	while (cp_env.var_env[i + 1] != NULL)
		if (swap_env(&cp_env, &i, tmp) == -1)
			return (error_msg(2, ' '));
	i = 0;
	while (cp_env.var_env[i] != NULL)
	{
		if (ft_strncmp(cp_env.var_env[i], "_=", 2) != 0)
		{
			if ((tmp = get_key_var_env(cp_env.var_env[i])) == NULL)
				return (error_msg(2, ' '));
			printf("declare -x %s=\"%s\"\n", tmp,
			get_value_var_env(get_var_env(env, cp_env.var_env[i])));
			free(tmp);
		}
		i++;
	}
	clear_env(&cp_env);
	return (0);
}

int	ft_export(char **arg, t_env **env)
{
	int	i;
	int	ret;
	int	res;

	i = 1;
	ret = 0;
	res = 0;
	if (arg[i] == NULL)
		return (sort_env(env, 0));
	if (arg[i] != NULL)
	{
		while (arg[i] != NULL)
		{
			res = check_arg_var(&arg[i], 1);
			if (res == 0)
			{
				if (process_add_var_env(arg[i], env) != 0)
					return (-1);
			}
			else if (res == 1)
			{
				error_msg_with_string(6, arg[i]);
				ret = 1;
			}
			i++;
		}
	}
	return (ret);
}
