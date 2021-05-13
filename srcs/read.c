/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 22:00:04 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/13 22:37:07 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_after_g_sig(t_termcap *t, t_env *env)
{
	g_sig.sig = 0;
	if (t->input != NULL)
		t->input = ft_free(t->input);
	t->pos_hist = 0;
	if (t->input_tmp != NULL)
		t->input_tmp = ft_free(t->input_tmp);
	env->return_value = 130;
}

int		process_read(t_termcap *t, int ret, int new_line, t_env *env)
{
	char	buff[BUFFER_SIZE + 1];

	init_read(t);
	while ((ret = read(0, &buff, BUFFER_SIZE)))
	{
		buff[ret] = '\0';
		if (g_sig.sig == 1)
			reset_after_g_sig(t, env);
		if ((new_line = check_char(buff, t)) <= 0)
			break ;
		if (new_line == 1)
			if ((t->input = ft_my_strjoin(t->input, buff)) == NULL)
				return (error_msg(2, ' '));
		get_pos_cursor(t);
		get_size_window(t);
	}
	ret = 0;
	if (new_line == 0 && g_sig.sig == 0 && t->input != NULL)
		ret = save_history(t->input, &t->history, t);
	else if (new_line == 0 && t->input == NULL)
		return (2);
	if (new_line == -1 || new_line == -2)
		return (new_line);
	return (ret);
}

int		loop_read(t_termcap *termcap, t_env *env)
{
	int	ret;

	prompt(termcap, env);
	if (swap_way_icanon_echo(0) != 0)
		return (-1);
	ret = process_read(termcap, 0, 1, env);
	if (termcap->history != NULL && ret == 0)
		termcap->line = ft_strdup(termcap->history->content);
	else if (ret == 2)
	{
		if ((termcap->line = malloc(sizeof(char))) != NULL)
			termcap->line[0] = '\0';
	}
	if (termcap->input != NULL)
		termcap->input = ft_free(termcap->input);
	if (swap_way_icanon_echo(1) != 0)
		ret = -1;
	if (termcap->line == NULL && (ret == 0 || ret == 2))
		return (error_msg(2, ' '));
	return (ret);
}
