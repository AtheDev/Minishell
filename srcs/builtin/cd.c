/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 10:48:10 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/19 17:32:20 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

int	process_cd(t_env **env, char *var_env, int num)
{
	char	*pwd;
	char	*oldpwd;
	char	*var;
	char	*path;

	if (num == 0)
	{
		var = get_var_env(env, var_env);
		pwd = get_var_env(env, "PWD");
		if (ft_strncmp(var_env, "OLDPWD", 6) == 0)
		{
			if (pwd == NULL && (var == NULL || var[ft_strlen(var_env) + 1] == '\0'))
			{
				error_msg_with_string(2, var_env);
				if (process_delete_var_env(var_env, env) != 0)
					return (error_msg(2, ' '));
				return (0);
			}
		}
		if (var == NULL)
			return (error_msg_with_string(2, var_env));
		if (var[ft_strlen(var_env) + 1] == '\0')
		{
			printf("Pas d'erreur => change le prompt \'~\' en \'/home/user42\'\n");
			return (0);
		}
		path = get_value_var_env(var);
	}
	else
		path = var_env;
	if (chdir(path) == 0)
	{
		pwd = get_value_var_env(get_var_env(env, "PWD"));
		oldpwd = get_value_var_env(get_var_env(env, "OLDPWD"));
		if (pwd == NULL)
		{
			if (oldpwd != NULL)
			{
				if (process_add_var_env(ft_strjoin("OLDPWD=", ""), env) == -1)
					return (error_msg(2, ' '));
			}
		}
		if (pwd != NULL && oldpwd != NULL)
		{
			if (pwd[0] == '\0')
				process_add_var_env(ft_strjoin("OLDPWD=", ""), env);
			else
		/*	if (*/process_add_var_env(ft_strjoin("OLDPWD=", pwd), env);
		/*	{
				process_free(pwd, oldpwd);
				return (error_msg(2, ' '));
			}*/
		}
	//	process_free(pwd, oldpwd);
		if (pwd != NULL)
		{
			pwd = getcwd(NULL, 0);
			if (pwd == NULL)
			{
				printf("Erreur lors de la récupération de PWD\n");
				return (1);
			}
			if (process_add_var_env(ft_strjoin("PWD=", pwd), env) == -1)
				return (error_msg(2, ' '));
			free(pwd);
		}
		if (ft_strncmp(var_env, "OLDPWD", 6) == 0)
			printf("%s\n", getcwd(NULL, 0));
	}
	else
	{
		printf("Erreur CHDIR\n");
		return (1);
	//	return (error_msg_with_string(1, var_env));
	}
	return (0);
}

int	ft_cd(char **arg, t_env **env)
{
	if (check_nb_arg(arg, 0) > 2)
		return (error_msg(4, ' '));
	if (arg[1] != NULL)
	{
		if (arg[1][0] == '\0')
			return (0);
		if (ft_strncmp(arg[1], "-", 2) == 0)
		{
			if (process_cd(env, "OLDPWD", 0) == 1)
				return (1);
			return (0);
		}
	}
	if (arg[1] == NULL || (arg[1] != NULL && ft_strncmp(arg[1], "--", 3) == 0))
	{
		if (process_cd(env, "HOME", 0) == 1)
			return (1);
		return (0);
	}
	else
	{
		if (process_cd(env, arg[1], 1) == 1)
			return (error_msg_with_string(1, arg[1]));
	}
	return (0);
}

