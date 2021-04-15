/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_escaped.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 00:40:42 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/16 00:47:31 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	db_quotes(char *str, int i)
{
	if (str[i] == '"' && is_escaped(str, i - 1) == 0)
		return (0);
	return (1);
}

int	sp_quote(char *str, int i)
{
	if (str[i] == '\'' && is_escaped(str, i - 1) == 0)
		return (0);
	return (1);
}

int	dollar(char *str, int i)
{
	if (str[i] == '$' && is_escaped(str, i - 1) == 0)
		return (0);
	return (1);
}

int	sep_cmd(char *str, int i)
{
	if ((str[i] == ';' || str[i] == '|') && is_escaped(str, i - 1) == 0)
		return (0);
	return (1);
}

int	redir(char *str, int i)
{
	if ((str[i] == '<' || str[i] == '>') && is_escaped(str, i - 1) == 0)
		return (0);
	return (1);
}
