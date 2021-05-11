/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:45:29 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/11 22:39:47 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	swap_env(t_env *cp, int *i, char *tmp, int size)
{
	if (ft_strncmp(cp->var_env[*i + 1], cp->var_env[*i], size) < 0)
	{
		if ((tmp = ft_strdup(cp->var_env[*i])) != NULL)
		{
			free(cp->var_env[*i]);
			if ((cp->var_env[*i] = ft_strdup(cp->var_env[*i + 1])) != NULL)
			{
				free(cp->var_env[*i + 1]);
				cp->var_env[*i + 1] = ft_strdup(tmp);
			}
		}
		if (tmp == NULL || cp->var_env[*i] == NULL ||
		cp->var_env[*i + 1] == NULL)
		{
			if (tmp != NULL)
				free(tmp);
			free_tab_string(cp->var_env);
			return (-1);
		}
		*i = 0;
	}
	else
		(*i)++;
	tmp = ft_free(tmp);
	return (0);
}

int	print_env(char **var_env, int i, t_env **env)
{
	char	*tmp;

	tmp = NULL;
	while (var_env[++i] != NULL)
	{
		if (ft_strncmp(var_env[i], "_=", 2) != 0)
		{
			if (ft_strchr(var_env[i], '=') != NULL)
			{
				if ((tmp = get_key_var_env(var_env[i])) == NULL)
					return (error_msg(2, ' '));
				printf("declare -x %s=\"%s\"\n", tmp,
				get_value_var_env(get_var_env(env, var_env[i])));
				tmp = ft_free(tmp);
			}
			else
				printf("declare -x %s\n", var_env[i]);
		}
	}
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
		if (swap_env(&cp_env, &i, tmp, ft_strlen(cp_env.var_env[i])) == -1)
			return (error_msg(2, ' '));
	print_env(cp_env.var_env, -1, env);
	clear_env(&cp_env);
	return (0);
}

int	ft_export(char **arg, t_env **env)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (arg[i] == NULL)
		return (sort_env(env, 0));
	if (arg[i] != NULL)
	{
		while (arg[i] != NULL)
		{
			if (check_arg_var(&arg[i], 1) == 0)
			{
				if (process_add_var_env(arg[i], env, 0, 1) != 0)
					return (-1);
			}
			else
			{
				error_msg_with_string(6, arg[i]);
				ret = 1;
			}
			i++;
		}
	}
	return (ret);
}
