/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:55:17 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/05 16:19:37 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prompt(t_termcap *t)
{
	char	*value;
	char	*tmp;
	char	*prompt;
	int	size;

	value = getcwd(NULL, 0);
	tmp = NULL;
	write(2, "\033[32mminishell\033[37m:", 21);
	if (value == NULL)
	{
		size = 10 + ft_strlen(t->save_pwd);
		tmp = ft_strjoin("\033[34m", t->save_pwd);
	}
	else
	{
		size = 10 + ft_strlen(value);
		t->save_prompt = ft_free(t->save_prompt);
		if ((t->save_prompt = ft_strdup(value)) != NULL)
			tmp = ft_strjoin("\033[34m", value);
		free(value);
	}
	prompt = ft_strjoin(tmp, "\033[37m");
	if (tmp != NULL)
		tmp = ft_free(tmp);
	ft_putstr_fd(prompt, 2);
	free(prompt);
	write(2, "$> ", 3);
	size += 3;
	if (t != NULL)
		t->size_prompt = size;
	return (1);
}
