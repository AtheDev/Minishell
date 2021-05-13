/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:57:47 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/13 15:56:11 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		process_cd(char *path, t_termcap *t, t_env **env)
{
	char	*tmp;

	if (chdir(path) == 0)
	{
		if ((tmp = getcwd(NULL, 0)) == NULL)
		{
			error_getcwd();
			if ((tmp = new_pwd(t, path)) == NULL)
				return (1);
		}
		if ((swap_pwd_oldpwd(t, tmp)) != 0)
		{
			if (tmp != NULL)
				tmp = ft_free(tmp);
			return (1);
		}
		if (update_var_env_pwd(env, t) != 0)
			return (1);
		if (update_var_env_oldpwd(env, t) != 0)
			return (1);
	}
	else
		return (error_msg_with_string(1, path));
	return (0);
}

int		process_cd_home(t_env **env, t_termcap *t)
{
	char	*home;

	home = get_value_var_env(get_var_env(env, "HOME"));
	if (home == NULL)
		return (error_msg_with_string(2, "HOME"));
	if (home[0] == '\0')
		return (0);
	else
		return (process_cd(home, t, env));
}

int		process_cd_oldpwd(t_env **env, t_termcap *t)
{
	char	*oldpwd;
	char	*tmp;

	tmp = NULL;
	oldpwd = get_value_var_env(get_var_env(env, "OLDPWD"));
	if (oldpwd == NULL)
		return (error_msg_with_string(2, "OLDPWD"));
	if (oldpwd[0] == '\0')
	{
		printf("\n");
		return (0);
	}
	else
	{
		process_cd(oldpwd, t, env);
		tmp = getcwd(NULL, 0);
		printf("%s\n", tmp);
		tmp = ft_free(tmp);
		return (0);
	}
}

int		ft_cd(char **arg, t_env **env, t_termcap *t)
{
	if (check_nb_arg(arg, 0) > 2)
		return (error_msg(4, ' '));
	if (arg[1] == NULL || ft_strncmp(arg[1], "~", 2) == 0)
		return (process_cd_home(env, t));
	else if (ft_strncmp(arg[1], "-", 2) == 0)
		return (process_cd_oldpwd(env, t));
	else if (arg[1][0] != '\0')
		return (process_cd(arg[1], t, env));
	return (0);
}
