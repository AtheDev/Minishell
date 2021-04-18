/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:41:45 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/18 11:24:31 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*edit_arg_db_quotes(char *str, int *i, t_env *env)
{
	str = delete_char(str, i);
	(*i)++;
	while (str[*i] != '"' || (str[*i] == '"' && is_escaped(str, *i - 1) == 1))
	{
		if (str[*i] == '\\' && str[*i + 1] == 'n')
			(*i)++;
		else if (str[*i] == '\\' && is_char(str[*i + 1], CHAR_PROTEC) == 0)
		{
			str = delete_char(str, i);
			(*i)++;
			if (str[*i + 1] == '"')
				break ;
		}
		else if (str[*i] == '$' && str[*i + 1] != '"')
			if (replace_variable(&str, i, env) == -1)
				return (NULL);
		if (str == NULL)
			return (NULL);
		(*i)++;
	}
	if (str[*i + 1] == '"')
		(*i)++;
	str = delete_char(str, i);
	(*i)--;
	return (str);
}

char	*edit_arg_other(char *str, int *i, t_env *env)
{
	while (((str[*i] != '"' && str[*i] != '\'') ||
	(str[*i] == '"' && is_escaped(str, *i - 1) == 1) ||
	(str[*i] == '\'' && is_escaped(str, *i - 1) == 1)) && str[*i] != '\0')
	{
		if (str[*i] == '\\' && str[*i + 1] == '\\')
		{
			if ((str = delete_char(str, i)) == NULL)
				return (NULL);
			(*i)++;
		}
		else if (str[*i] == '\\' && str[*i + 1] != '\\')
		{
			if ((str = delete_char(str, i)) == NULL)
				return (NULL);
			(*i)++;
		}
		else if (str[*i] == '$' && str[*i + 1] != '\0' && str[*i + 1] != '\\')
		{
			if (replace_variable(&str, i, env) == -1)
				return (NULL);
		}
		(*i)++;
	}
	(*i)--;
	return (str);
}

char	*edit_arg(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			str = edit_arg_db_quotes(str, &i, env);
		else if (str[i] == '\'')
		{
			if ((str = delete_char(str, &i)) == NULL)
				return (NULL);
			i++;
			while (str[i] != '\'')
				i++;
			str = delete_char(str, &i);
		}
		else
			str = edit_arg_other(str, &i, env);
		if (str == NULL)
			return (NULL);
		i++;
	}
	return (str);
}

int		dvlpmt_arg(char **arg, t_env *env)
{
	int	i;
	i = -1;
	while (arg[++i] != NULL)
	{
		arg[i] = edit_arg(arg[i], env);
		printf("arg[%d] = %s\n", i, arg[i]);
		if (arg[i] == NULL)
			return (error_msg(2, ' '));
	}
	return (0);
}

