/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 22:35:41 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/13 22:36:50 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	key_delete(t_termcap *t, int size)
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

int	up_and_down(char *buff, t_termcap *t)
{
	if (buff[0] == '\x1b' && buff[1] == '[' && buff[2] == 'A')
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
	return (0);
}

int	check_char(char *buff, t_termcap *t)
{
	if (buff[0] == '\n')
	{
		if (t->input_tmp != NULL)
			t->input_tmp = ft_free(t->input_tmp);
		return (write(1, "\n", 1) - 1);
	}
	else if (buff[0] == '\04' && t->pos_cursor == t->size_prompt)
		return (-2);
	else if (buff[0] == '\x1b' && buff[1] == '[' &&
	(buff[2] == 'A' || buff[2] == 'B'))
		return (up_and_down(buff, t));
	else if (buff[0] == 127)
		return (key_delete(t, 0));
	else if ((buff[0] == '\x1b' && buff[1] == '[' && (buff[2] == 'C' ||
	buff[2] == 'D')) || buff[0] == 27 || ft_isprint(buff[0]) == 0)
		return (2);
	t->pos_cursor++;
	write(1, &buff[0], 1);
	return (1);
}
