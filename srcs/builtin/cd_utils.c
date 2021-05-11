/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 23:17:43 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/11 23:31:20 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_getcwd(void)
{
	ft_putstr_fd("minishell: cd : error determining the current directory:", 2);
	ft_putstr_fd(" getcwd: cannot access parent directories: ", 2);
	ft_putstr_fd("No file or folder of this type\n", 2);
}

int		update_var_env_pwd(t_env **env, t_termcap *t)
{
	char	*pwd;
	char	*tmp;

	pwd = get_value_var_env(get_var_env(env, "PWD"));
	if (pwd != NULL)
	{
		if ((tmp = ft_strjoin("PWD=", t->save_pwd)) != NULL)
		{
			if ((process_add_var_env(tmp, env, 0, 1)) == -1)
			{
				tmp = ft_free(tmp);
				return (error_msg(2, ' '));
			}
			tmp = ft_free(tmp);
		}
		else
			return (error_msg(2, ' '));
	}
	return (0);
}

int		update_var_env_oldpwd(t_env **env, t_termcap *t)
{
	char	*oldpwd;
	char	*tmp;

	oldpwd = get_value_var_env(get_var_env(env, "OLDPWD"));
	if (oldpwd != NULL)
	{
		if ((tmp = ft_strjoin("OLDPWD=", t->save_oldpwd)) != NULL)
		{
			if ((process_add_var_env(tmp, env, 0, 1)) == -1)
			{
				tmp = ft_free(tmp);
				return (error_msg(2, ' '));
			}
			tmp = ft_free(tmp);
		}
		else
			return (error_msg(2, ' '));
	}
	return (0);
}

int		swap_pwd_oldpwd(t_termcap *t, char *tmp)
{
	t->save_oldpwd = ft_free(t->save_oldpwd);
	t->save_oldpwd = ft_strdup(t->save_pwd);
	t->save_pwd = ft_free(t->save_pwd);
	t->save_pwd = ft_strdup(tmp);
	tmp = ft_free(tmp);
	if (t->save_oldpwd == NULL || t->save_pwd == NULL)
		return (error_msg(2, ' '));
	return (0);
}

char	*new_pwd(t_termcap *t, char *path)
{
	char	*tmp;
	int		size;

	tmp = NULL;
	size = ft_strlen(path) + ft_strlen(t->save_pwd) + 2;
	tmp = malloc(sizeof(char) * (size));
	if (tmp != NULL)
	{
		ft_bzero(tmp, size);
		ft_strcpy(tmp, t->save_pwd);
		ft_strncat(tmp, "/", 1);
		ft_strncat(tmp, path, ft_strlen(path));
		return (tmp);
	}
	error_msg(2, ' ');
	return (NULL);
}
