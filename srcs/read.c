/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 22:00:04 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/05 17:19:28 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		key_delete(t_termcap *t, int size)
{
	if (t->size_prompt < t->pos_cursor)
	{
		size = ft_strlen(t->input) - 1;
		if (((int)ft_strlen(t->input) + t->size_prompt >= t->cols_window)
		&& (t->cols_cursor == 1))
		{
			tputs(tgoto(t->move_cursor, t->cols_window,
					t->rows_cursor - 2), 0, &ft_putchar);
			tputs(t->del_char, 0, &ft_putchar);
			t->input = delete_char(t->input, &size);
			t->pos_cursor--;
		}
		else
		{
			tputs(t->move_left, 0, &ft_putchar);
			tputs(t->del_char, 0, &ft_putchar);
			t->input = delete_char(t->input, &size);
			t->pos_cursor--;
		}
		if (t->input == NULL)
			return (error_msg(2, ' '));
	}
	return (2);
}

int		check_char(char *buff, t_termcap *t)
{
	if (buff[0] == '\n')
	{
		if (t->input_tmp != NULL)
			t->input_tmp = ft_free(t->input_tmp);
		return (write(1, "\n", 1) - 1);
	}
	else if (buff[0] == '\04' && t->pos_cursor == t->size_prompt)
		return (-2);
	else if (buff[0] == '\x1b' && buff[1] == '[' && buff[2] == 'A')
	{
		if (t->history != NULL && t->pos_hist < t->tot_hist)
			return (up_history(t));
		return (2);
	}
	else if (buff[0] == '\x1b' && buff[1] == '[' && buff[2] == 'B')
	{
		if (t->history != NULL && t->pos_hist > 0)
			down_history(t);
		return (2);
	}
	else if (buff[0] == 127)
		return (key_delete(t, 0));
	else if ((buff[0] == '\x1b' && buff[1] == '[' && (buff[2] == 'C' ||
	buff[2] == 'D')) || buff[0] == 27 || ft_isprint(buff[0]) == 0)
		return (2);
	t->pos_cursor++;
	write(1, &buff[0], 1);
//	if ((t->pos_cursor % t->cols_window) == 0)
//		write(1, "\r\n", 2);
	return (1);
}

void	reset_after_g_sig(t_termcap *t, t_env *env)
{
	g_sig = 0;
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
		if (g_sig == 1)
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
	if (new_line == 0 && g_sig == 0 && t->input != NULL)
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

	prompt(termcap);
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
