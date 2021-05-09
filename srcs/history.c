/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:25:03 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/09 22:44:41 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		save_history(char *input, t_list **history, t_termcap *t)
{
	t_list	*new;

	if (*history != NULL)
	{
		if (ft_strncmp((*history)->content, input, ft_strlen(input) + 1) == 0)
			return (0);
	}
	if ((new = ft_lstnew(ft_strdup(input))) == NULL)
		return (error_msg(2, ' '));
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

void	print_history(t_list **hist, int index, t_termcap *t, t_env *env)
{
	t_list	*hist_tmp;
	int		i;

	hist_tmp = *hist;
	i = -1;
	while ((++i < (index - 1)) && (i < (t->tot_hist - 1)))
		*hist = (*hist)->next;
	if (g_sig == 0)
		prompt(t, env);
	if (t->pos_hist > 0)
		ft_putstr_fd((*hist)->content, 1);
	else if (t->pos_hist == 0)
		ft_putstr_fd(t->input_tmp, 1);
	if (t->input != NULL)
		t->input = ft_free(t->input);
	if (t->pos_hist > 0)
		t->input = ft_strdup((*hist)->content);
	else if (t->pos_hist == 0)
		t->input = ft_strdup(t->input_tmp);
	if (t->input == NULL)
		return ;
	t->pos_cursor = ft_strlen(t->input) + t->size_prompt;
	*hist = hist_tmp;
}

void	delete_line_history(t_termcap *t)
{
	int	count;
	int	size;

	count = 0;
	size = 0;
	if (t->input != NULL)
		size = (int)ft_strlen(t->input);
	if (size + t->size_prompt >= t->cols_window)
	{
		count = ((int)ft_strlen(t->input) + t->size_prompt) / t->cols_window;
		while (count > 0)
		{
			tputs(t->del_line, 0, &ft_putchar);
			tputs(tgoto(t->move_cursor, 1, t->rows_cursor - 2), 0, &ft_putchar);
			t->rows_cursor--;
			count--;
		}	
	}
	//	tputs(tgoto(t->move_cursor, t->save_col_cursor, t->rows_cursor - 2), 0, &ft_putchar);
	//	tputs(t->del_many_char, 0, &ft_putchar);
	//	t->rows_cursor--;
//	}
}

int		up_history(t_termcap *t, t_env *env)
{
	if (t->pos_hist == 0)
	{
		if (t->input_tmp != NULL)
			t->input_tmp = ft_free(t->input_tmp);
	}
	if (t->input != NULL && t->pos_hist == 0)
		t->input_tmp = ft_strdup(t->input);
	else if (t->input == NULL && t->pos_hist == 0)
		t->input_tmp = ft_strdup("");
	if (t->pos_hist == 0 && t->input_tmp == NULL)
		return (error_msg(2, ' '));
	delete_line_history(t);
	tputs(t->del_line, 0, &ft_putchar);
	if (t->pos_hist != t->tot_hist)
		t->pos_hist++;
	print_history(&t->history, t->pos_hist, t, env);
	return (2);
}

int		down_history(t_termcap *t, t_env *env)
{
	delete_line_history(t);
	tputs(t->del_line, 0, &ft_putchar);
	if (t->pos_hist > 0)
		t->pos_hist--;
	print_history(&t->history, t->pos_hist, t, env);
	return (2);
}
