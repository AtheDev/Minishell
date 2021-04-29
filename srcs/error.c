/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 22:15:53 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/29 18:05:48 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(int num, char c)
{
	if (num == 1 || num == 5)
	{
		ft_putstr_fd("minishell: syntax error near unexpected symbol « ", 2);
		write(2, &c, 1);
		if (num == 5)
			write(2, &c, 1);
		ft_putstr_fd(" »\n", 2);
		return (1);
	}
	if (num == 2)
	{
		ft_putstr_fd("minishell: error: malloc failed\n", 2);
		return (-1);
	}
	if (num == 3)
		ft_putstr_fd("minishell: multiline is not accepted\n", 2);
	if (num == 4)
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	return (1);
}

int	putstr(char *str1, char *str2, char *str3)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	return (0);
}

int	error_msg_with_string(int num, char *str)
{
	if (num == 1)
		putstr("minishell: cd: ", str, " : no such file or directory\n");
	if (num == 2)
		putstr("minishell: cd: « ", str, " » undefined\n");
	if (num == 3)
		putstr("minishell: ", str, ": too many arguments\n");
	if (num == 4)
		putstr("minishell: exit: ", str, " : numeric argument rquired\n");
	if (num == 5)
		putstr("minishell: unset: « ", str, " » : not a valid identifier\n");
	if (num == 6)
		putstr("minishell: export: « ", str, " » : not a valid identifier\n");
	if (num == 7)
		putstr("env: «", str, "» : no such file or directory\n");
	if (num == 8)
		putstr("minishell: ", str, ": command not found\n");
	return (1);
}

int	error_term(int num, char *str)
{
	if (num == 1)
		ft_putstr_fd("Could not access to the termcap database..\n", 2);
	if (num == 2)
	{
		putstr("Terminal type '", str, "' is not defined in termcap ");
		ft_putstr_fd("database (or have too few informations).\n", 2);
	}
	return (-1);
}
