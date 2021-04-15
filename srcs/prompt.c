/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:55:17 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/16 00:05:46 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prompt(void)
{
	char	*value;
	char	*tmp;
	char	*prompt;

	value = getcwd(NULL, 0);
	write(2, "\033[32mminishell\033[37m:", 21);
	tmp = ft_strjoin("\033[34m", value);
	free(value);
	prompt = ft_strjoin(tmp, "\033[37m");
	free(tmp);
	ft_putstr_fd(prompt, 2);
	free(prompt);
	write(2, "$> ", 3);
	return (1);
}
