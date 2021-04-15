/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 22:15:53 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/16 00:19:07 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(int num, char c)
{
	if (num == 1)
		printf("Erreur de syntaxe près du symbole inattendu « %c »\n", c);
	if (num == 2)
	{
		printf("Error: malloc failed\n");
		return (-1);
	}
	if (num == 3)
		printf("minishell: multiline is not accepted\n");
	if (num == 4)
		printf("minishell: cd: too many arguments\n");
	return (1);
}

int	error_msg_with_string(int num, char *str)
{
	if (num == 1)
		printf("minishell: cd: %s: no such file directory\n", str);
	if (num == 2)
		printf("minishell: cd: « %s » undefined\n", str);
	return (0);
}
