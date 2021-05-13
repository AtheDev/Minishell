/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 17:24:42 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/12 17:27:28 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		loop_db_quotes(int *i, char **str, t_env *env)
{
	if ((*str)[*i] == '\\' && (*str)[*i + 1] == 'n')
		(*i)++;
	else if ((*str)[*i] == '\\' && is_char((*str)[*i + 1], CHAR_PROTEC) == 0)
	{
		*str = delete_char(*str, i);
		(*i)++;
		if (*str != NULL && (*str)[*i + 1] == '"')
		{
			(*i)++;
			return (0);
		}
	}
	else if ((*str)[*i] == '$' && (ft_isalnum((*str)[*i + 1]) == 1 ||
	(*str)[*i + 1] == '_' || (*str)[*i + 1] == '?'))
	{
		if (replace_variable(str, i, env) == -1)
			return (-1);
	}
	if (*str == NULL)
		return (-1);
	(*i)++;
	return (1);
}

char	*edit_arg_db_quotes(char *str, int *i, t_env *env)
{
	int	ret;

	ret = 0;
	if ((str = delete_char(str, i)) == NULL)
		return (NULL);
	(*i)++;
	while (str[*i] != '"' || (str[*i] == '"' && is_escaped(str, *i - 1) == 1))
	{
		ret = loop_db_quotes(i, &str, env);
		if (ret == -1)
			return (NULL);
		if (ret == 0)
			break ;
	}
	if ((str = delete_char(str, i)) == NULL)
		return (NULL);
	(*i)++;
	return (str);
}

int		edit_arg_sp_quote(int *i, char **str)
{
	if ((*str = delete_char(*str, i)) == NULL)
		return (-1);
	(*i)++;
	while ((*str)[*i] != '\'')
		(*i)++;
	if ((*str = delete_char(*str, i)) == NULL)
		return (-1);
	if ((*str)[0] == '\0')
		return (0);
	return (1);
}
