/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:09:43 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/28 16:21:16 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_term(t_env *env)
{
	char		*term_type;
	int	ret;

	term_type = get_value_var_env(get_var_env(&env, "TERM="));
	if (term_type == NULL)
		return (-1);
	ret = tgetent(NULL, term_type);
	if (ret == -1)
		return (error_term(1, ""));
	else if (ret == 0)
		return (error_term(2, term_type));
	return (0);
}

int	swap_way_icanon_echo(int num)
{
	struct termios	t_term;

	errno = 0;
	if (tcgetattr(0, &t_term) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (-1);
	}
	if (num == 0)
		t_term.c_lflag &= ~ (ICANON | ECHO);
	else if (num == 1)
		t_term.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, 0, &t_term) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (-1);
	}
	return (0);
}
