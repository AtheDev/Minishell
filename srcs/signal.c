/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 10:59:21 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/28 10:59:57 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sigint(int num)
{
	(void)num;
	if (g_sig != 0 && g_sig != 1)
		ft_putstr_fd("\n", 1);
	else
	{
		ft_putstr_fd("^C\n", 1);
		prompt(NULL);
		g_sig = 1;
	}
}

void	handler_sigquit(int num)
{
	(void)num;
	if (g_sig != 0)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}
