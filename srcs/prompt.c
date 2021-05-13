/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:55:17 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/12 08:41:37 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_diff_with_var_env(char *str, t_env *env, t_termcap *t)
{
	char	*pwd;

	pwd = get_value_var_env(get_var_env(&env, "PWD"));
	if (pwd == NULL)
		return (str);
	if (ft_strncmp(str, pwd, ft_strlen(pwd)) != 0)
	{
		str = ft_free(str);
		if ((str = ft_strdup(pwd)) == NULL)
			return (NULL);
		if (t->save_pwd != NULL)
			t->save_pwd = ft_free(t->save_pwd);
		t->save_pwd = ft_strdup(str);
	}
	return (str);
}

char	*get_value_prompt(char *value, t_termcap *t, t_env *env, int *size)
{
	char	*tmp;

	tmp = NULL;
	if (value == NULL)
	{
		*size = 10 + ft_strlen(t->save_pwd);
		tmp = ft_strjoin("\033[34m", t->save_pwd);
	}
	else
	{
		if ((value = check_diff_with_var_env(value, env, t)) != NULL)
		{
			*size = 10 + ft_strlen(value);
			t->save_prompt = ft_free(t->save_prompt);
			if ((t->save_prompt = ft_strdup(value)) != NULL)
				tmp = ft_strjoin("\033[34m", value);
			free(value);
		}
	}
	return (tmp);
}

int		prompt(t_termcap *t, t_env *env)
{
	char	*value;
	char	*tmp;
	char	*prompt;
	int		size;

	value = getcwd(NULL, 0);
	tmp = NULL;
	size = 0;
	write(2, "\033[32mminishell\033[37m:", 21);
	tmp = get_value_prompt(value, t, env, &size);
	if (tmp == NULL)
		tmp = "";
	prompt = ft_strjoin(tmp, "\033[37m");
	if (tmp != NULL && tmp[0] != '\0')
		tmp = ft_free(tmp);
	ft_putstr_fd(prompt, 2);
	free(prompt);
	write(2, "$> ", 3);
	size += 3;
	if (t != NULL)
		t->size_prompt = size;
	return (1);
}
