/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 22:00:04 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/26 22:43:28 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_history(char *input, t_list **history, t_termcap *t)
{
	t_list	*new;

	if (input == NULL)
		return (1);
	if (*history != NULL)
	{
		if (ft_strncmp((*history)->content, input, ft_strlen(input) + 1) == 0)
			return (0);
	}
	if ((new = ft_lstnew(input)) == NULL)
		return (-1);
	if (*history != NULL)
	{
		new->next = *history;
		*history = new;
	}
	else
		*history = new;
	t->tot_hist++;
	return (0);
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

void	print_history(t_list **hist, int index, char **input, t_termcap *t)
{
	t_list *hist_tmp;
	int	i;

	hist_tmp = *hist;
	i = 0;
	while ((i < (index - 1)) && (i < (t->tot_hist - 1)))
	{
		*hist = (*hist)->next;
		i++;
	}
	if (g_sig == 0)
		prompt(t);
	if (t->pos_hist > 0)
	{
		ft_putstr_fd((*hist)->content, 1);
		*input = ft_strdup((*hist)->content);
		t->pos_cursor = ft_strlen(*input) + t->size_prompt;
	}
	else if (t->pos_hist == 0)
	{
		ft_putstr_fd(t->input_tmp, 1);
		*input = ft_strdup(t->input_tmp);
		t->pos_cursor = ft_strlen(*input) + t->size_prompt;	
	}
	*hist = hist_tmp;
}

int	check_char(char *buff, t_termcap *t)
{
	if (buff[0] == '\n')
	{
		write(2, "\n", 1);
		return (0);
	}
	else if (buff[0] == '\x1b' && buff[1] == '[' && buff[2] == 'A')
	{
		if (t->history != NULL)
		{
			if (t->input != NULL && t->pos_hist == 0)
				t->input_tmp = ft_strdup(t->input);
			else if (t->input == NULL && t->pos_hist == 0)
				t->input_tmp = ft_strdup("");
			tputs(t->del_line, 0, &ft_putchar);
			if (t->pos_hist != t->tot_hist)
				t->pos_hist++;
			print_history(&t->history, t->pos_hist, &t->input, t);	
		}
		return (2);
	}
	else if (buff[0] == '\x1b' && buff[1] == '[' && buff[2] == 'B')
	{
		if (t->history != NULL && t->pos_hist > 0)
		{
			tputs(t->del_line, 0, &ft_putchar);
			if (t->pos_hist > 0)
				t->pos_hist--;
			print_history(&t->history, t->pos_hist, &t->input, t);
		}
		return (2);
	}
	else if (buff[0] == '\x1b' && buff[1] == '[' && (buff[2] == 'C' || buff[2] == 'D'))
		return (2);
	else if (buff[0] == 127)
	{
		if (t->size_prompt < t->pos_cursor)
		{
			int	size = ft_strlen(t->input) - 1;
			tputs(t->move_left, 0, &ft_putchar);
			tputs(t->del_char, 0, &ft_putchar);
			t->input = delete_char(t->input, &size);
			t->pos_cursor--;
		}
		return (2);
	}
	else if (buff[0] == 27)
		return (2);
	else
	{
		write(1, &buff[0], 1);
		t->pos_cursor++;
	}
	return (1);
}

int	process_read(t_termcap *t)
{
	char	buff[BUFFER_SIZE + 1];
	int	ret;
	int	new_line;

	new_line = 1;
	t->pos_hist = 0;
	t->pos_cursor = t->size_prompt;
	g_sig = 0;
	t->input_tmp = NULL;
	while ((ret = read(0, &buff, BUFFER_SIZE)) && new_line == 1)
	{
		buff[ret] = '\0';
		if (g_sig == 1)
		{
			g_sig = 0;
			if (t->input != NULL)
				free(t->input);
			t->input = NULL;
			
		}
		new_line = check_char(buff, t);
		if (new_line == -1 || new_line == 0)
			break ;
		if (new_line == 1)
			t->input = ft_my_strjoin(t->input, buff);
		if (new_line == 2)
			new_line = 1;
	}
	ret = 0;
	if (new_line == 0 && g_sig == 0 && t->input != NULL)
		ret = save_history(t->input, &t->history, t);
	else if (new_line == 0 && t->input == NULL)
		return (2);
	t->input = NULL;
	return (ret);
}