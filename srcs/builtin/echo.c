/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 10:24:02 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/06 23:39:57 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option_echo(char *str, int i)
{
	if (str == NULL)
		return (1);
	if (str[i] == '-')
	{
		i++;
		if (str[i] == 'n')
		{
			while (str[i] != '\0')
			{
				if (str[i] != 'n')
					return (1);
				i++;
			}
			return (0);
		}
	}
	return (1);
}

int	ft_echo(char **arg, int i, int n, int nb_arg)
{
	int	ret;

	ret = 0;
	if (arg[1] != NULL)
	{
		if (check_option_echo(arg[1], 0) == 0)
			n = 1;
	}
	i = i + n;
	if (arg[i] != NULL || (arg[i] == NULL && i < nb_arg))
	{
		while (check_option_echo(arg[i], 0) == 0)
			i++;
		while (i < nb_arg)
		{
			if (i == (nb_arg - 1) && arg[i] == NULL)
			{
				i++;
				continue ;
			}
			if (arg[i] == NULL)
				write(1, " ", 1);
			else if (arg[i][0] != '\0')
			{
				write(1, arg[i], ft_strlen(arg[i]));
				if (arg[i + 1] != NULL || (arg[i + 1] == NULL && (i + 1) < nb_arg))
					write(1, " ", 1);
			}
			i++;
		}
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}

