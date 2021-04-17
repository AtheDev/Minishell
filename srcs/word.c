/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 11:17:19 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/17 11:23:52 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_word(char *str, int i, int quote)
{
	(void)quote;
	while (str[i] != '\0')
	{
		if (str[i] == '`' && is_escaped(str, i - 1) == 0)
			return (error_msg(3, ' '));
		i++;
	}
	return (0);
}

int	delete_space2(char **cmd, int *i, int num)
{
	if (num == 0)
	{
		while ((((*cmd)[*i] != ' ' && (*cmd)[*i] != '"' && (*cmd)[*i] != '\'')
		|| ((*cmd)[*i] == '"' && is_escaped(*cmd, *i - 1) == 1) ||
		((*cmd)[*i] == ' ' && is_escaped(*cmd, *i - 1) == 1) ||
		((*cmd)[*i] == '\'' && is_escaped(*cmd, *i - 1) == 1))
		&& (*cmd)[*i] != '\0')
			(*i)++;
		(*i)--;
	}
	if (num == 1)
	{
		(*i)++;
		while ((*cmd)[*i] == ' ' && (*cmd)[*i] != '\0')
		{
			*cmd = delete_char(*cmd, i);
			if (*cmd == NULL)
				return (error_msg(2, ' '));
			(*i)++;
		}
		(*i)--;
	}
	return (0);
}

int	delete_space(char **cmd, int i)
{
	while ((*cmd)[++i] != '\0')
	{
		if ((*cmd)[i] != '"' && (*cmd)[i] != ' ' && (*cmd)[i] != '\'')
			delete_space2(cmd, &i, 0);
		else if (db_quotes(*cmd, i) == 0)
		{
			i++;
			while (((*cmd)[i] != '"' || ((*cmd)[i] == '"' &&
			is_escaped(*cmd, i - 1) == 1)))
				i++;
		}
		else if (sp_quote(*cmd, i) == 0)
		{
			i++;
			while ((*cmd)[i] != '\'')
				i++;
		}
		else if ((*cmd)[i] == ' ' && is_escaped(*cmd, i - 1) == 0)
		{
			if (delete_space2(cmd, &i, 1) == -1)
				return (-1);
		}
	}
	return (0);
}
