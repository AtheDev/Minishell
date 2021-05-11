/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 11:15:35 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/11 23:41:03 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_buff(t_termcap *t, char *buff)
{
	int	i;
	int	res;

	i = 0;
	if (buff[i] == 27)
		i++;
	if (buff[i] == 91)
		i++;
	res = 0;
	while (buff[i] != 59)
	{
		res = res * 10 + (buff[i] - 48);
		i++;
	}
	t->rows_cursor = res;
	i++;
	res = 0;
	while (buff[i] != 82)
	{
		res = res * 10 + (buff[i] - 48);
		i++;
	}
	t->cols_cursor = res;
}

void	get_pos_cursor(t_termcap *t)
{
	char	buff[255];
	int		ret;

	if ((write(STDOUT_FILENO, "\x1b[6n", 4)) != 4)
		return ;
	if ((ret = read(STDIN_FILENO, &buff, 254)) == -1)
		return ;
	buff[ret] = '\0';
	read_buff(t, buff);
	return ;
}

int		get_size_window(t_termcap *t)
{
	struct winsize	ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
		return (-1);
	else
	{
		t->cols_window = ws.ws_col;
		t->rows_window = ws.ws_row;
	}
	return (0);
}
