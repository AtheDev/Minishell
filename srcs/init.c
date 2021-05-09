/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:14:25 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/09 22:44:05 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_home(char *str)
{
	char	*tmp;
	int		i;
	int		slash;

	i = -1;
	slash = 0;
	while (slash < 3)
	{
		++i;
		if (str[i] == '/')
			slash++;
	}
	if ((tmp = malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	ft_strlcpy(tmp, str, i + 1);
	return (tmp);
}

int	save_pwd(t_env *env, t_termcap *t)
{
	if ((t->save_prompt = getcwd(NULL, 0)) == NULL)
		return (error_msg(2, ' '));
	if (env->size > 2)
	{
		t->save_home = ft_strdup(get_value_var_env(get_var_env(&env, "HOME")));
		t->save_oldpwd = ft_strdup(get_value_var_env(get_var_env(&env, "OLDPWD")));
		t->save_pwd = ft_strdup(get_value_var_env(get_var_env(&env, "PWD")));	
	}
	else
	{
		t->save_pwd = ft_strdup(t->save_prompt);
		t->save_oldpwd = ft_strdup(t->save_prompt);
		t->save_home = find_home(t->save_prompt);
	}
	if (t->save_home == NULL || t->save_oldpwd == NULL || t->save_pwd == NULL)
		return (error_msg(2, ' '));
	return (0);
}

int	init2(t_env *env, char **envp, t_termcap *t)
{
	g_sig = 0;
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, handler_sigquit);
	if (*envp != NULL)
	{
		*env = copy_env(envp, 1, 0);
		if (env->var_env == NULL)
			return (1);
	}
	else
	{
		*env = init_env_null();
		if (env->var_env == NULL)
			return (1);
	}
	if (init_term(env) != 0)
		return (1);
	if (save_pwd(env, t) != 0)
		return (1);
//printf("prompt = %s | home = %s | pwd = %s | oldpwd = %s\n", t->save_prompt, t->save_home, t->save_pwd, t->save_oldpwd);
	t->history = NULL;
	//t->save_prompt = getcwd(NULL, 0);
	t->tot_hist = 0;
	t->del_char = tgetstr("dc", NULL);
	t->del_line = tgetstr("dl", NULL);
//	t->del_many_char = tgetstr("ce", NULL);
	t->move_left = tgetstr("le", NULL);
	t->move_cursor = tgetstr("cm", NULL);
	return (0);		
}

void	init(t_list **cmd_tmp, t_list_cmd **cmd, t_termcap *t)
{
	*cmd_tmp = NULL;
	*cmd = NULL;
	t->line = NULL;
	t->input = NULL;
}

void	init_read(t_termcap *t)
{
	get_pos_cursor(t);
//	t->save_row_cursor = t->rows_cursor;
//	t->save_col_cursor = t->cols_cursor - t->size_prompt;
//ft_putnbr_fd(t->save_col_cursor, 2);
	get_size_window(t);
	t->rows_prompt = t->rows_cursor;
	t->cols_prompt = 1;
	t->pos_hist = 0;
	t->pos_cursor = t->size_prompt;
	g_sig = 0;
	t->input_tmp = NULL;
}
